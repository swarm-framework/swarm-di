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

#ifndef SWARM_DI_INJECTABLE_HXX
#define SWARM_DI_INJECTABLE_HXX

namespace swarm {
    namespace di {

        /// \brief Class Scope
        struct Injectable {
            virtual ~Injectable(){};
        };

        /// \brief Request scope, one instant per request (manually opened and closed)
        struct RequestScope : public Injectable {};

        /// \brief Application scope, one during all application life
        struct ApplicationScope : public Injectable {};
    }
}

#endif // SWARM_DI_INJECTABLE_HXX
