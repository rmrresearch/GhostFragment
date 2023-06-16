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
#include "utilities/strings/string_tools.hpp"
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <sstream>
#include <vector>

namespace utilities::printing {

/** @brief An std::ostream that automatically wraps its contents if they
 *         exceed the specified width.
 *
 *  WordWrapStream instances wrap another `std::ostream` instance. The resulting
 *  WordWrapStram instance prints to the wrapped instance and behaves exactly
 *  like the wrapped instance except that internally the WordWrapStream tracks
 *  how many characters have been printed and will automatically insert a line
 *  break when printing a word would cause the current line to have more
 *  characters than a predefined width. The word wrap only occurs if the user
 *  does not provide a newline character prior to a line reaching the predefined
 *  width. If a newline character is encountered before that, the internal
 *  counter is reset. Hence this class will preserve pre-existing formatting.
 */
class WordWrapStream : private std::streambuf, public std::ostream {
public:
    /// The type used to specify the predefined width
    using width_type = unsigned long;

    /** @brief Bestows an existing ostream with word wrapping abalities
     *
     * @param[in] os The address of the ostream instance we are wrapping. The
     *               lifetime of the ostream is not managed by the resulting
     *               WordWrapStream and it is the user's responsibility to
     *               ensure @p os stays in scope.
     * @param[in] w  The predefined width at which word wrapping occurs. Default
     *               is 80 characters.
     *
     * @throw std::bad_alloc if there is insufficient memory to make the PIMPL
     *                       instance. Strong throw guarantee.
     */
    explicit WordWrapStream(std::ostream* os, width_type w = 80) :
      std::ostream(this), m_os_(os), m_w_(w) {}

protected:
    // This function does the heavy lifting
    std::streamsize xsputn(const char* s, std::streamsize n) override {
        // Break paragraph into sentences
        auto sentences = strings::split_string(std::string(s, s + n), "\n");

        const auto nsentences = sentences.size();
        for(std::size_t si = 0; si < nsentences; ++si) { // Loop over sentences
            auto sentence = sentences[si];
            while(!sentence.empty()) {
                const unsigned short size = sentence.size();
                if(m_nchars_ + size <= m_w_) { // Whole thing fits
                    (*m_os_) << sentence;
                    m_nchars_ += size;
                    break;
                }

                // Remainder of this while figures out where to break the line

                // How many characters do we have left?
                const auto char_left = m_w_ - m_nchars_;

                // Find the first space we can break on
                std::size_t offset = sentence.find(' ', 0);

                // Was there any spaces left?
                const bool no_spaces_left = (offset == std::string::npos);

                // Aren't on empty line and can't print any part of what remains
                if((no_spaces_left || offset > char_left) && m_nchars_ > 0) {
                    (*m_os_) << std::endl;
                    m_nchars_ = 0;
                    continue;
                }

                if(no_spaces_left) {
                    (*m_os_) << sentence;
                    break;
                }

                // See if we can fit more on the line
                while(offset != std::string::npos) {
                    auto temp = sentence.find(' ', offset + 1);
                    if(temp > char_left || temp == std::string::npos) break;
                    offset = temp;
                }

                (*m_os_) << sentence.substr(0, offset);
                (*m_os_) << std::endl;
                m_nchars_ = 0;
                sentence  = sentence.substr(offset + 1); // swallow the space
            }
            // Print a newline if we have more lines left
            if(si < nsentences - 1) {
                (*m_os_) << std::endl;
                m_nchars_ = 0;
            }

        } // loop over lines
        return n;
    }

    int overflow(std::streambuf::int_type c) override {
        if(m_nchars_ == m_w_) {
            (*m_os_) << std::endl;
            m_nchars_ = 0;
        }
        (*m_os_) << std::streambuf::traits_type::to_char_type(c);
        ++m_nchars_;

        return c;
    }

private:
    /// Where we write data to if an overflow occurs
    std::ostream* m_os_;

    /// The width of the page
    width_type m_w_;

    /// How many characters we've written
    width_type m_nchars_ = 0;
};

} // namespace utilities::printing
