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

#ifndef SWARM_DI_INJECT_HXX
#include "Inject.hxx"
#endif

#include <swarm/exception/SwarmException.hxx>
#include "InjectableEntry.hxx"

namespace swarm {
    namespace di {
        
        template<class Object>
        std::map<std::string, std::shared_ptr<InjectableEntry>> Inject<Object>::entries_;
            
        template<class Object>
        Inject<Object>::Inject(const std::string & name) : name_(name) {
        }
        
        // Return 
        template<class Object>
        std::shared_ptr<Object> Inject<Object>::get() {
            
            // FIXME Convert to supplier
            
            // Test injectable
            if(std::is_base_of<Injectable, Object>::value) {
                
                // Find existing entry
                auto entry = Inject<Object>::entries_[name_];

                // Create if doesn't exists
                if (!entry) {

                    // Test application
                    if(std::is_base_of<ApplicationScope, Object>::value) {

                        // Create entry
                        entry = std::make_shared<InjectableEntry>(
                            name_,
                            std::shared_ptr<scope::MemoizableScope>{new scope::MemoizableScope},
                            []() {
                                return std::shared_ptr<Injectable>{new Object{}};
                            }
                        );

                    // Test Request
                    } else if(std::is_base_of<RequestScope, Object>::value) {
                        
                        // Create entry
                        entry = std::make_shared<InjectableEntry>(
                            name_,
                            std::shared_ptr<scope::RequestScope>{new scope::RequestScope},
                            []() {
                                return std::shared_ptr<Injectable>{new Object{}};
                            }
                        );
                        
                    } else {

                        // Create direct creation entry
                        entry = std::make_shared<InjectableEntry>(
                            name_,
                            std::shared_ptr<scope::DirectScope>{new scope::DirectScope},
                            []() {
                                return std::shared_ptr<Injectable>{new Object{}};
                            }
                        );
                    }

                    // Add applications
                    Inject<Object>::entries_[name_] = entry;
                }

                // Test entry
                if (entry) {
                    return entry->defaultScope().template get<Object>(entry);
                }
                
                throw SwarmException{"Unable to find or create instance for %1%", name_};
            }
            
            return std::make_shared<Object>();
        }
        
        template<class Object>
        const std::string & Inject<Object>::name() const {
            return name_;
        }
    }
}
