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

// FIXME A supprimer
#include <iostream>

namespace swarm {
    namespace di {
        
        template<class Object>
        std::map<std::string, std::shared_ptr<Injectable>> Inject<Object>::applications_;
            
        template<class Object>
        Inject<Object>::Inject(const std::string & name) : name_(name) {
        }
        
        // Return 
        template<class Object>
        std::shared_ptr<Object> Inject<Object>::get() {
            
            // Test injectable
            if(std::is_base_of<Injectable, Object>::value) {
                
                std::cout << "Injectable" << std::endl;
                
                // Test application
                if(std::is_base_of<ApplicationScope, Object>::value) {
                    std::cout << "Application" << std::endl;
                    
                    std::shared_ptr<Injectable> object = Inject<Object>::applications_[name_];
                    if (!object) {
                        object = std::make_shared<Object>();
                        Inject<Object>::applications_[name_] = object; 
                    }
                    return std::dynamic_pointer_cast<Object>(object);
                }

            }
            
            return std::make_shared<Object>();
        }
        
        template<class Object>
        const std::string & Inject<Object>::name() const {
            return name_;
        }
    }
}
