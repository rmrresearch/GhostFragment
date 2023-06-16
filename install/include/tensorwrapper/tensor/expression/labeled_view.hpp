/*
 * Copyright 2022 NWChemEx-Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <memory>
#include <optional>
#include <string>
#include <tensorwrapper/tensor/expression/expression_class.hpp>
#include <tensorwrapper/tensor/fields.hpp>

namespace tensorwrapper::tensor {
template<typename FieldType>
class TensorWrapper;

namespace expression {

/** @brief Associates an annotation with a reference to a tensor.
 *
 *  This class associates a set of labels with a reference to a tensor. In
 *  particular this means the LabeledView instance does not manage the lifetime
 *  of the TensorWrapper used to create it and it is the caller's responsibility
 *  to ensure the TensorWrapper remains in scope until the LabeledView goes out
 *  of scope.
 *
 *  In practice lifetime management is straightforward because LabeledView
 *  objects are typically unnamed temporaries. For example:
 *  ```
 *  TensorWrapper a,b,c;
 *  c("i,j") = a("i,k") * b("k,j");
 *  ```
 *  Here the three calls to TensorWrapper::operator(std::string) create
 *  three unnamed LabeledView instances, all of which are out of scope after
 *  the multiplication.
 *
 *  The only thing slightly tricky about this class is getting the const
 *  correctness right. In most expression layers this is done by having const
 *  show up somewhere in the type argument. We avoid this by having the class
 *  hold either a read/write reference or a read-only reference to the tensor.
 *  For the most part everything just works. The only hiccup comes from when you
 *  a non-const LabeledView instance, but it was initialized with a const
 *  reference (say from a const TensorWrapper object). In this case calling
 *  `tensor()` will throw as it would violate const-correctness by returing a
 *  read/write reference. Instead the user needs to call `tensor() const` to get
 *  back the read-only reference. In practice end users of TensorWrapper usually
 *  interact with this class implicitly, so this is only a complication seen by
 *  developers of TensorWrapper (it only really affects the Expression class).
 */
template<typename FieldType>
class LabeledView {
public:
    /// Type of the tensor this is a view of
    using tensor_type = TensorWrapper<FieldType>;

    /// Type of a read/write reference to the tensor this is a view of
    using tensor_reference = tensor_type&;

    /// Type of a read-only reference to the tensor this is a view of
    using const_tensor_reference = const tensor_type&;

    /// Type used to label the modes of the tensor
    using label_type = std::string;

    /// Type of a read-only reference to the tensor's labels
    using const_label_reference = const label_type&;

    /// Type resulting from promoting this instance to the expression layer
    using expression_type = Expression<FieldType>;

    /// Read-only reference to object in the expression layer
    using const_expression_reference = const expression_type&;

    // -------------------------------------------------------------------------
    // -- Ctors and dtor
    // -------------------------------------------------------------------------

    /** @brief Annotates a read/write view of a tensor.
     *
     *  This ctor creates a labeled view of @p tensor. Since @p tensor need not
     *  be initialized (e.g., if it appears on the left side of an assignment
     *  operation) no checks will be performed to ensure that @p labels are
     *  consistent with @p tensor.
     *
     *  It should be noted that the resulting LabeledView only aliases
     *  @p tensor and it is thus the caller's responsibilty to manage the
     *  lifetime of @p tensor, in particular the caller needs to ensure
     *  @p tensor does not go out of scope while the LabeledView instance is
     *  still in use.
     *
     *  @param[in] labels The annotation for @p tensor.
     *  @param[in] tensor The tensor this is a view of.
     *
     *  @throw None No throw guarantee.
     */
    LabeledView(label_type labels, tensor_reference tensor) noexcept;

    /** @brief Annotates a read-only view of a tensor.
     *
     *  This ctor behaves identical to the read/write view ctor except that the
     *  resulting LabeledView instance will enforce read-only access to the
     *  aliased tensor. Notably this means that attempting to call `tensor()`
     *  instead of `tensor() const` will raise an exception.
     *
     *  @param[in] labels The annotation for @p tensor.
     *  @param[in] tensor The tensor this is a view of.
     *
     *  @throw None No throw guarantee.
     */
    LabeledView(label_type labels, const_tensor_reference tensor) noexcept;

    /** @brief Creates a new LabeledView which is a copy of @p other.
     *
     *  This ctor will create a new LabeledView which is a deep copy of @p
     *  other. However, since views of a tensor have alias semantics, the deep-
     *  copy of the view also has alias semantics of the same tensor. The labels
     *  are actually deep copied. (It's a deep copy in the sense that the
     *  holder in the copy is not an alias of the holder in the original, but
     *  immediately following the copy both holders will alias the same tensor.)
     *
     *  @param[in] other The LabeledView we are deep copying.
     *
     *  @throw std::bad_alloc if there is a problem deep copying the labels.
     *                        Strong throw guarantee. (Copying the tensor
     *                        reference is no-throw guarantee.)
     */
    LabeledView(const LabeledView& other) = default;

    /** @brief Creates a new LabeledView which owns the state of @p other.
     *
     *  This ctor creates a new LabeledView by moving the new instance's state
     *  from @p other. The resulting LabeledView will still alias the same
     *  tensor.
     *
     *  @param[in,out] other The view we are taking the state from. After this
     *                       operation @p other is in a valid, but otherwise
     *                       undefined state.
     *
     *  @throw None No throw guarantee.
     */
    LabeledView(LabeledView&& other) noexcept = default;

    /// Default no-throw dtor (N.B. the aliased tensor is NOT cleaned-up)
    ~LabeledView() noexcept = default;

    // -------------------------------------------------------------------------
    // -- Accessors
    // -------------------------------------------------------------------------

    /** @brief Wraps this LabeledView in an Expression class.
     *
     *  The expression layer describes how pieces of tensor equations are
     *  combined. Every piece of the expression layer must be wrapped in an
     *  Expression instance. This method creates a new Expression instance by
     *  wrapping *this.
     *
     *  @return An Expression instance that contains a copy of *this. Note that
     *          this means the resulting Expression still aliases the same
     *          tensor.
     *
     *  @throw std::bad_alloc if there is problem creating the Expression
     *                        instance. Strong throw guarantee.
     */
    expression_type expression() const;

    /** @brief Provides read/write access to the aliased tensor.
     *
     *  This method should only be used if this LabeledView is holding a
     *  read/write tensor.
     *
     *  @return The tensor aliased by *this.
     *
     *  @throw std::runtime_error if this instance is wrapping a read-only
     *                            tensor. Strong throw guarantee.
     */
    tensor_reference tensor();

    /** @brief Provides read-only access to the aliased tensor.
     *
     *  This method will return the aliased tensor in a read-only state
     *  regardless of whether we are aliasing a read/write or read-only tensor.
     *
     *  @return The tensor aliased by *this.
     *
     *  @throw std::runtime_error if this instance is not holding a tensor. In
     *                            general this state can only be achieved by
     *                            trying to use a LabeledView instance after
     *                            moving from it. Strong throw guarantee.
     */
    const_tensor_reference tensor() const;

    /** @brief Provides read-only access to the labels annotating the tensor.
     *
     *
     *  @return The labels associated with the aliased tensor.
     *
     *  @throw None No throw guarantee.
     */
    const_label_reference labels() const { return m_labels_; }

    // -------------------------------------------------------------------------
    // -- Assignment operations
    // -------------------------------------------------------------------------

    /** @brief Overwrites the contents by transforming @p rhs
     *
     *  @warning In general this is NOT just copy assignment.
     *
     *  This method is copy assignment only when:
     *
     *  - this instance has the same labels as @p rhs, and
     *  - this instance aliases a default constructed TensorWrapper
     *
     *  In all other circumstances this method represents a transformation of
     *  @p rhs. Arguably the most common use case is permutation of the modes of
     *  @p rhs. An example of such an invocation is something like:
     *  ```
     *  TensorWrapper a, b;
     *  a("i,j") = b("j,i");
     *  ```
     *  In this example, after the operation, `a` will contain `b` transposed.
     *  The other possible transformations are syntactic sugar for reallocating
     *  or reshaping @p rhs. These transformations occur if the tensor aliased
     *  by *this contains a different allocator and/or shape than @p rhs.
     *
     *  @param[in] rhs The input to transform into the tensor wrapped by *this
     *
     *  @return The current instance after transforming it according to the
     *          operation defined by the comparing the shapes, allocators, and
     *          labels in *this and @p rhs.
     *
     *  @throw std::runtime_error if *this holds a read-only tensor and thus can
     *                            not be assigned to. Strong throw guarantee.
     *
     *  @throws std::bad_alloc if there is a problem allocating memory for the
     *                         temporary expression.
     */
    LabeledView& operator=(const LabeledView& rhs);

    /** @brief Overwrites the contents by evaluating @p rhs
     *
     *  This method behaves similar to operator=(LabeledView) except that @p rhs
     *  is in general a more complicated expression than simply a labeled
     *  tensor. Upon invocation, this method will:
     *
     *  - set the allocator for this->tensor()
     *  - set the shape for this->tensor()
     *  - set the buffer for this->buffer()
     *  - return *this
     *
     *  It should be noted that if the allocator and/or shape of this->tensor()
     *  is already set that allocator and/or shape will be used (assuming the
     *  values are compatible with evaluation of @p rhs).
     *
     *  @param[in] rhs The expression we are evaluating and assigning to *this.
     *
     *  @return The current instance after assigning the result of @p rhs to it.
     *
     *  @throws std::runtime_error if *this contains a read-only tensor and thus
     *                             can not be assigned to. Strong throw
     *                             guarantee.
     *
     *  @throws ??? If the expression throws. Same throw guarantee as the
     *              expression.
     */
    LabeledView& operator=(const_expression_reference rhs);

    // -------------------------------------------------------------------------
    // -- Math operations
    // -------------------------------------------------------------------------

    /** @brief Creates an expression that sums *this and @p rhs
     *
     *  @return an Expression instance which, when evaluated, will return the
     *          result of summing *this and @p rhs.
     *
     *  @throw std::bad_alloc if there is a problem allocating the state for the
     *                        returned object. Strong throw guarantee.
     */
    expression_type operator+(const LabeledView& rhs) const;

    /** @brief Creates an expression that subtracts @p rhs from *this.
     *
     *  @param[in] rhs The LabeledView being subtracted from *this.
     *
     *  @return an Expression instance, which when evaluated, will return the
     *          result of subtracting @p rhs from *this
     *
     *  @throw std::bad_alloc if there is a problem allocationg the state for
     *                        the returned object. Str
     */
    expression_type operator-(const LabeledView& rhs) const;

    /** @brief Creates an expression that multiplies *this by  @p rhs
     *
     *  This operation will multiply *this by @p rhs. Whether this is an
     *  element-wise multiplication, a contraction, or a combination of both is
     *  ultimately determined by the labels on *this, the labels on @p rhs, and
     *  the labels on the tensor the expression is assigned to.
     *
     *  @param[in] rhs The LabeledView being multiplied with *this.
     *
     *  @return an Expression instance, which when evaluated, will return the
     *          result of subtracting @p rhs from *this
     *
     *  @throw std::bad_alloc if there is a problem allocationg the state for
     *                        the returned object. Str
     */
    expression_type operator*(const LabeledView& rhs) const;

    /** @brief Creates an expression that creates a scaled version of *this
     *
     *
     *  @param[in] rhs The scalar to scale *this by.
     *
     *  @return An Expression instance which, when evaluated, will result in
     *          the product of *this and @p rhs.
     *
     *  @throw std::bad_alloc if there is a problem allocating the Expression.
     *                        Strong throw guarantee.
     */
    expression_type operator*(double rhs) const;

    // -------------------------------------------------------------------------
    // -- Utility
    // -------------------------------------------------------------------------

    /** @brief Determines if two labeledView instances are value equal
     *
     *  Two LabeledView instances are value equal if they both contain the
     *  same set of labels, both alias the same tensor, and if they both alias
     *  the tensor with the same const-ness (i.e., they both either alias the
     *  tensor by read/write alias or they both alias it read-only).
     *
     *  @param[in] rhs The labeled view we are comparing to.
     *
     *  @return True if *this is value equal to @p rhs and false otherwise.
     *
     *  @throw None no throw guarantee.
     */
    bool operator==(const LabeledView& rhs) const noexcept;

    /** @brief Determines if two LabeledView instances are different.
     *
     *  This method simply negates operator==. See the description there for the
     *  definition of value equal.
     *
     *  @return False if *this is the same as @p rhs and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const LabeledView& rhs) const noexcept;

private:
    /// How we store read/write references internally
    using internal_reference = std::reference_wrapper<tensor_type>;

    /// How we store read-only references internally
    using internal_const_reference = std::reference_wrapper<const tensor_type>;

    /// The labels for the tensor
    label_type m_labels_;

    /// If we're aliasing a read/write tensor it'll be here
    std::optional<internal_reference> m_tensor_;

    /// If we're aliasing a read-only tensor it'll be here
    std::optional<internal_const_reference> m_ctensor_;
};

extern template class LabeledView<field::Scalar>;
extern template class LabeledView<field::Tensor>;

} // namespace expression
} // namespace tensorwrapper::tensor

/** @brief Allows labeled views to be scaled from the left side
 *
 *  @related LabeledView
 *
 *  In order to support an operation like `a("i,j) = 3.14 * b("i,j")` we need to
 *  overload double's operator*. This overload simply dispatches to
 *  LabeledView::operator*(double), i.e., we assume that scalar multiplication
 *  is always commutative.
 *
 *  @param[in] lhs The scalar we are multiplying @p rhs by.
 *  @param[in] rhs The view of the tensor being scaled.
 *
 *  @return An expression object describing the desired operation.
 */
template<typename FieldType>
tensorwrapper::tensor::expression::Expression<FieldType> operator*(
  double lhs,
  const tensorwrapper::tensor::expression::LabeledView<FieldType>& rhs) {
    return rhs * lhs;
}
