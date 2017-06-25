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
#define SWARM_DI_INJECT_HXX

#include <memory>
#include <string>

namespace swarm {
    namespace di {

        /// \brief Class Inject
        template<class Object>
        class Inject {
            
        private:
            
            /// \brief Injection name
            std::string name_;
            
        public:
            
            /// \brief Constructor with name
            /// \param name Injection name
            Inject(const std::string & name);
            
            /// \return Name
            const std::string & name() const;
            
            /// \return Return object
            std::shared_ptr<Object> get();
        };
    }
}

#include "Inject.txx"

#endif // SWARM_DI_INJECT_HXX
