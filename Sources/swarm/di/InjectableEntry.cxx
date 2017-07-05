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

#include "InjectableEntry.hxx"

namespace swarm {
    namespace di {

        // Constructor with factory
        InjectableEntry::InjectableEntry(const std::string & name,
                        std::shared_ptr<Scope> scope, 
                        std::function<std::shared_ptr<Injectable>()> factory) : name_(name), scope_(scope), factory_(factory) {
            
        }
        
        // String containing entry name
        const std::string & InjectableEntry::name() const {
            return name_;
        }
        
        // Retrieve default scope
        Scope & InjectableEntry::defaultScope() {
            return *(scope_.get());
        }
        
        // Create new instance
        std::shared_ptr<Injectable> InjectableEntry::newInstance() const {
            return factory_();
        }
    }
}
