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
#include <tensorwrapper/tensor/field/traits.hpp>

namespace tensorwrapper::tensor::expression {
namespace detail_ {

template<typename FieldType>
class ExpressionPIMPL;

}

/** @brief A piece of a type-erased tensor expression.
 *
 *  Doing math with TensorWrapper instances uses a domain specific language
 *  (DSL). Expression instances are type-erased pieces of the DSL. By using
 *  type-erasure (as opposed to expression templating which is more common) it
 *  is easier to perform runtime manipulations on the Expression layer. Each
 *  piece of the DSL contains a lazy operation. For example an Expression
 *  instance meant to add two tensors, will simply hold two Expression instances
 *  (which themselves are also lazy operations) and not add the sub instances
 *  together until told to (by calling tensor()).
 *
 *  @tparam FieldType A strong type indicating whether the tensors in the
 *                    expression contain scalars or tensors as elements.
 *                    Expected to be either field::Scalar or field::Tensor.
 */
template<typename FieldType>
class Expression {
private:
    /// The type of the FieldTraits instance setting most of this class's types
    using ft = field::FieldTraits<FieldType>;

public:
    /// Type used to label tensors. Ultimately defined by
    /// FieldTraits<FieldType>::label_type
    using label_type = typename ft::label_type;

    /// Type of a read-only reference to labels. Ultimately defined by
    /// FieldTraits<FieldType>::const_label_reference
    using const_label_reference = typename ft::const_label_reference;

    /// Type of a tensor. Defined by FieldTraits<FieldType>::tensor_type.
    using tensor_type = typename ft::tensor_type;

    /// Type of a read-only Allocator. Ultimately defined by
    /// FieldTraits<FieldType>::const_allocator_reference
    using const_allocator_reference = typename ft::const_allocator_reference;

    /// Type of a read-only Shape. Ultimately defined by
    /// FieldTraits<FieldType>::const_shape_reference
    using const_shape_reference = typename ft::const_shape_reference;

    /// Type of the object implementing *this
    using pimpl_type = detail_::ExpressionPIMPL<FieldType>;

    /// Type of a pointer to a pimpl_type instance
    using pimpl_pointer = std::unique_ptr<pimpl_type>;

    // -------------------------------------------------------------------------
    // -- Ctors, Assignment Operators, and Dtor
    // -------------------------------------------------------------------------

    /** @brief Creates a new empty Expression.
     *
     *  This Ctor creates an empty Expression (i.e., an Expression wrapping
     *  no state). Empty Expression instances are typically used as
     *  placeholders. To convert an empty Expression to a non-empty Expression
     *  a user must assign a non-empty Expressio to it.
     *
     *  @throw None No throw guarantee.
     */
    explicit Expression() noexcept;

    /** @brief Creates a new Expression with the specified state.
     *
     *  This Ctor can be used to create either an empty or non-empty Expression.
     *  Providing a null pointer will create an empty Expression, whereas
     *  providing a non-null pointer creates a non-empty Expression. Users of
     *  TensorWrapper will in general not directly create non-empty Expression
     *  instances. Rather, non-empty Expression instances are created
     *  automatically by the DSL.
     *
     *  @param[in] p A PIMPL to the implementation.
     *
     *  @throw None No throw guarantee.
     */
    explicit Expression(pimpl_pointer p) noexcept;

    /** @brief Creates a new Expression which is a deep copy of @p other.
     *
     *  This ctor creates a new Expression which is a deep copy of @p other.
     *  In practice Expression instances are defined in terms of LabeledView
     *  instances (which alias TensorWrapper instances on deep copy) .
     *
     *  @param[in] other The Expression to copy.
     *
     *  @throw std::bad_alloc This method throws if calling the PIMPL's copy
     *                        ctor throws. At the moment PIMPL copy ctors only
     *                        throw if there is a problem allocating. Strong
     *                        throw guarantee
     */
    Expression(const Expression& other);

    /** @brief Creates a new Expression which takes ownership of the state in
     *         @p other.
     *
     *  This ctor passes ownership of @p other's internal state to the newly
     *  created instance.
     *
     *  @param[in,out] other The Expression we are taking the state from. After
     *                       calling this method @p other will be in an empty
     *                       state.
     *
     *  @throw None No throw guarantee.
     */
    Expression(Expression&& other) noexcept;

    /** @brief Set the state of *this to a deep copy of the state in @p rhs
     *
     *  This method will overwrite the state *this holds (freeing it up in the
     *  process) with a deep copy of the state in @p rhs.
     *
     *  @param[in] rhs The instance whose state is being copied.
     *
     *  @return *this after setting the internal state to a deep copy of @p rhs.
     *
     *  @throw std::bad_alloc This method throws if calling the PIMPL's copy
     *                        ctor throws. At the moment PIMPL copy ctors only
     *                        throw if there is a problem allocating. Strong
     *                        throw guarantee
     */
    Expression& operator=(const Expression& rhs);

    /** @brief Set the state of *this to the state in @p rhs.
     *
     *  This method will overwrite the state of *this (freeing it up in the
     *  process) with the state contained in @p rhs.
     *
     *  @param[in,out] rhs The instance whose state is being transferred to
     *                     *this. After this method @p rhs will behave like an
     *                     empty Expression.
     *
     *  @return *this after taking ownership of the state in @p rhs.
     *
     *  @throw None no throw guarantee.
     */
    Expression& operator=(Expression&& rhs) noexcept;

    /// Default no-throw dtor
    ~Expression() noexcept;

    // -------------------------------------------------------------------------
    // -- Operators
    // -------------------------------------------------------------------------

    /** @brief Adds *this to @p rhs
     *
     *  @param[in] rhs The Expression being added to *this.
     *
     *  @return An Expression instance, which when evaluated will return the
     *          sum of *this and @p rhs.
     *
     *  @throw std::runtime_error If *this or @p rhs is empty. Strong throw
     *                            guarantee.
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL for
     *                        the return. Strong throw guarantee.
     */
    Expression operator+(const Expression& rhs) const;

    /** @brief Subtracts @p rhs from *this
     *
     *  @param[in] rhs The Expression being subtracted from *this.
     *
     *  @return An Expression instance, which when evaluated will return the
     *          difference between *this and @p rhs.
     *
     *  @throw std::runtime_error If *this or @p rhs is empty. Strong throw
     *                            guarantee.
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL for
     *                        the return. Strong throw guarantee.
     */
    Expression operator-(const Expression& rhs) const;

    /** @brief Scales *this by @p rhs
     *
     *  @param[in] rhs The value to scale *this by.
     *
     *  @return An Expression instance, which when evaluated will return the
     *          scale *this by @p rhs.
     *
     *  @throw std::runtime_error if *this is empty. Strong throw guarantee.
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL for
     *                        the return. Strong throw guarantee.
     */
    Expression operator*(double rhs) const;

    /** @brief Multiplies *this and @p rhs
     *
     *  This operator is used for element-wise multiplication and contractions.
     *  Whether the operation is element-wise, contraction, or a mixture depends
     *  on the labels of the tensors involved.
     *
     *  @param[in] rhs The Expression being multiplied with *this.
     *
     *  @return An Expression instance, which when evaluated will return the
     *          product of *this and @p rhs.
     *
     *  @throw std::runtime_error If *this or @p rhs is empty. Strong throw
     *                            guarantee.
     *  @throw std::bad_alloc if there is a problem allocating the PIMPL for
     *                        the return. Strong throw guarantee.
     */
    Expression operator*(const Expression& rhs) const;

    // -------------------------------------------------------------------------
    // -- DSL Evaluators
    // -------------------------------------------------------------------------

    /** @brief Determines the labels for the tensor resulting from this
     *         expression.
     *
     *  Expressions are typically a tree-like object in which each Expression
     *  instance contains sub-Expression instances. The entire treee ultimately
     *  gets assigned to a labeled tensor. This method is given the target
     *  labels for the entire expression tree and returns the labels for the
     *  sub-tree held in *this. For simple trees the result of this call will
     *  usually just be @p lhs_labels; however, for more complicated trees the
     *  result may differ depending on whether it is possible to account for
     *  permutations of modes in the wrapped operations.
     *
     *  @param[in] lhs_labels The labels on the tensor to which the entire
     *                        Expression tree is being assigned.
     *
     *  @return The labels for the tensor in to which *this should be assigned.
     *          Note that sub-expressions are evaluated into temporary tensors
     *          and the result need not equal @p lhs_labels
     *
     *  @throw std::runtime_error If *this is empty. Strong throw guarantee.
     */
    label_type labels(const_label_reference lhs_labels) const;

    /** @brief Evaluates *this into a tensor with the specified state.
     *
     *  This method is used to actually evaluate *this. The inputs to this
     *  method describe the tensor instance in to which *this is being directly
     *  assigned (this may only be a temporary intermediate and not represent
     *  the final result). It is this method's responsibility to do any
     *  transformation necessary to put the contents of *this into such a
     *  tensor.
     *
     *
     *  @param[in] labels The labels for the tensor *this is being assigned to.
     *  @param[in] shape  The shape object of the tensor *this is being assigned
     *                    to.
     *  @param[in] alloc The allocator for the tensor *this is being assigned
     *                   to.
     *
     *  @return The tensor resulting from evaluating *this.
     *
     *  @throw std::runtime_error if *this is empty. Strong throw guarantee.
     *
     */
    tensor_type tensor(const_label_reference labels,
                       const_shape_reference shape,
                       const_allocator_reference alloc) const;

    // -------------------------------------------------------------------------
    // -- Utility Methods
    // -------------------------------------------------------------------------

    /** @brief Is the Expression instance empty?
     *
     *  An Expression instance is empty if it does not contain a PIMPL. This
     *  can occur because the Expression was default initialized, initialized
     *  with a null pointer, or because it was moved from. This method can be
     *  used to determine if the Expression is empty.
     *
     *  @return True if *this is empty and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool is_empty() const noexcept;

    /** @brief Exchanges the state of two Expression instances
     *
     *  This method will swap the state of two Expression instances.
     *
     *  @param[in,out] rhs The instance whose state is being exchanged with
     *                     *this. After this call @p rhs will have the state
     *                     *this had prior to the call.
     *
     *  @throw None No throw guarantee.
     */
    void swap(Expression& rhs) noexcept;

    /** @brief Determines if two Expression instances are value equal.
     *
     *  Two Expression instances are value equal if they are both empty or if
     *  they both contain PIMPLs which are value equal. PIMPLs are value equal
     *  if they both describe the same operation (e.g., both are addition or
     *  both are multiplication), and if any subexpressions comapre value equal.
     *  N.B. that recursion stops when reaching labeled tensors and the
     *  subexpressions wrapping the labeled tensors are value equal if the
     *  labels on the tensors are equal and the tensors compare value equal.
     *
     *  @param[in] rhs The instance being compared to *this.
     *
     *  @return True if *this is value equal to @p rhs and false otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator==(const Expression& rhs) const noexcept;

    /** @brief Determines if two Expression instances are different.
     *
     *  This function simply negates operator==. In turn we define two
     *  Expression instances as different if they are not value equal. See the
     *  description of operator== for the definition of value equal.
     *
     *  @param[in] rhs The instance being compared to *this.
     *
     *  @return False if *this is value equal to @p rhs and true otherwise.
     *
     *  @throw None No throw guarantee.
     */
    bool operator!=(const Expression& rhs) const noexcept;

private:
    /// Type of a reference to a read-only pimpl_type
    using const_pimpl_reference = const pimpl_type&;

    /// Asserts that we have a pimpl
    void assert_pimpl_() const;

    /// Checks we have a PIMPL (throws std::runtime_error if not) and returns it
    const_pimpl_reference pimpl_() const;

    /// The actua implementation of *this
    pimpl_pointer m_pimpl_;
};

extern template class Expression<field::Scalar>;
extern template class Expression<field::Tensor>;

} // namespace tensorwrapper::tensor::expression
