/*
 * Copyright 2017 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef SWARM_DI_SCOPE_HXX
#define SWARM_DI_SCOPE_HXX

#include <memory>
#include <map>
#include <string>

namespace swarm {
    namespace di {

        struct Injectable;
        class InjectableEntry;
        
        /// \brief Scope
        struct Scope {
            
            /// \brief Virtual descriptor
            virtual ~Scope() {}
            
            /// \brief Get injectable object
            /// \param entry Injectable entry to found or create
            /// \return An injectable object or an invalid pointer
            virtual std::shared_ptr<Injectable> get(const InjectableEntry & entry) = 0;
            
            /// \brief Get injectable object
            /// \param entry Injectable entry to found or create
            /// \return An injectable object or an invalid pointer
            virtual std::shared_ptr<Injectable> get(const std::shared_ptr<InjectableEntry> entry);
            
            /// \brief Get typed injectable object
            /// \return An injectable object of type O or an invalid pointer
            template <class O>
            std::shared_ptr<O> get(const InjectableEntry & entry);
            
            /// \brief Get typed injectable object
            /// \return An injectable object of type O or an invalid pointer
            template <class O>
            std::shared_ptr<O> get(const std::shared_ptr<InjectableEntry> entry);
            
        };
        
        namespace scope {
            
            /// \brief Scope wich create new instance every call of get method
            struct DirectScope : public Scope {
                
                /// \brief Get injectable object
                /// \param entry Injectable entry to found or create
                /// \return An injectable object or an invalid pointer
                virtual std::shared_ptr<Injectable> get(const InjectableEntry & entry);
            };
            
            /// \brief Scope creating only once object in application
            class MemoizableScope : public Scope {
                
            private:
                
                /// \brief Store all objects
                std::map<std::string, std::shared_ptr<Injectable>> objects_;
                
            public:
                
                /// \brief Get injectable object
                /// \param entry Injectable entry to found or create
                /// \return An injectable object or an invalid pointer
                virtual std::shared_ptr<Injectable> get(const InjectableEntry & entry);
            };
            
            /// \brief Define a request scope
            class RequestScope : public Scope {
                
            private:
                
                /// \brief define per thread storage
                thread_local static std::shared_ptr<MemoizableScope> memoizableScope_;
                
            public:
                
                /// \brief Get injectable object
                /// \param entry Injectable entry to found or create
                /// \return An injectable object or an invalid pointer
                virtual std::shared_ptr<Injectable> get(const InjectableEntry & entry);
                
                /// \brief reset request storage
                static void reset();
                
                /// \brief reset request storage
                /// \param scope Init with sub scope
                static void init(std::shared_ptr<MemoizableScope> scope);
            };
        }
    }
}

#include "Scope.txx"

#endif // SWARM_DI_SCOPE_HXX
