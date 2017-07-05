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
#include "Scope.hxx"
#endif // SWARM_DI_SCOPE_HXX

#include "InjectableEntry.hxx"

namespace swarm {
    namespace di {
        
            // Get injectable object
            std::shared_ptr<Injectable> Scope::get(const std::shared_ptr<InjectableEntry> entry) {
               return get(*entry);
            }
                
            namespace scope {
                
                // Get injectable object
                std::shared_ptr<Injectable> DirectScope::get(const InjectableEntry & entry) {
                    return entry.newInstance();
                }
                
                // Get injectable object
                std::shared_ptr<Injectable> MemoizableScope::get(const InjectableEntry & entry) {
                    
                    // Find object
                    auto object = objects_[entry.name()];
                    if (!object) {
                        
                        // Create object
                        object = entry.newInstance();
                        
                        // Save it
                        objects_[entry.name()] = object;
                    }
                    
                    return object;
                }
                
                // Init local storage
                thread_local std::shared_ptr<MemoizableScope> RequestScope::memoizableScope_ = std::make_shared<MemoizableScope>();
                                
                // Get injectable object
                std::shared_ptr<Injectable> RequestScope::get(const InjectableEntry & entry) {
                    return RequestScope::memoizableScope_->get(entry);
                }
                
                // reset request storage
                void RequestScope::reset() {
                    RequestScope::memoizableScope_ = std::make_shared<MemoizableScope>();
                }
                
                // reset request storage
                void RequestScope::init(std::shared_ptr<MemoizableScope> scope) {
                    RequestScope::memoizableScope_ = scope;
                }
            }
    }
}
