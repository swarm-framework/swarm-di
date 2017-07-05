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

#ifndef SWARM_DI_INJECTABLEENTRY_HXX
#define SWARM_DI_INJECTABLEENTRY_HXX

#include "Scope.hxx"
#include <memory>
#include <string>
#include <functional>

namespace swarm {
    namespace di {

        struct Injectable;
        
        /// \brief Class InjectableEntry
        class InjectableEntry {
            
        private:
            
            /// \brief Entry name
            std::string name_;
            
            /// \brief Scope
            std::shared_ptr<Scope> scope_;
            
            /// \brief Factory
            std::function<std::shared_ptr<Injectable>()> factory_;
            
            /// \brief Remove default constructor
            InjectableEntry() = delete;
            
        public:
            
            /// \brief Constructor with factory
            /// \param name Entry name
            /// \param scope Scope
            /// \param factory Fatcory
            InjectableEntry(const std::string & name,
                            std::shared_ptr<Scope> scope, 
                            std::function<std::shared_ptr<Injectable>()> factory);
            
            /// \return String containing entry name
            const std::string & name() const;
            
            /// \return Retrieve default scope
            Scope & defaultScope();
            
            /// \brief Create new instance
            /// \return New injectable instance
            std::shared_ptr<Injectable> newInstance() const;
        };
    }
}

#endif // SWARM_DI_INJECTABLEENTRY_HXX
