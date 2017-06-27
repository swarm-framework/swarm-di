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

#include <catch/catch.hxx>

#include <swarm/di/Inject.hxx>
#include <swarm/di/Injectable.hxx>

using namespace swarm::di;

namespace swarm {
    namespace test {
                
        class ObjectToInject : public Injectable {
            
        public:
            static int count_;
            static int launch_;
        public:
            
            ObjectToInject() {
                ++ObjectToInject::count_;
            }
            
            void launch() {
                ++ObjectToInject::launch_;
            }
        };
        
        int ObjectToInject::count_ = 0;
        int ObjectToInject::launch_ = 0;
        
                        
        class ApplicationObjectToInject : public ApplicationScope {
            
        public:
            static int count_;
            static int launch_;
        public:
            
            ApplicationObjectToInject() {
                ++ApplicationObjectToInject::count_;
            }
            
            void launch() {
                ++ApplicationObjectToInject::launch_;
            }
        };
        
        int ApplicationObjectToInject::count_ = 0;
        int ApplicationObjectToInject::launch_ = 0;

        class ObjectInject {
        
        private:
            Inject<ObjectToInject> object1ToInject_{"Object1OnDemand"};
            Inject<ApplicationObjectToInject> object2ToInject_{"Object2OnApplicationScope"};
            
        public:
            void launch() {
                object1ToInject_.get()->launch();
                object2ToInject_.get()->launch();
            }
        };
    }   
}

using namespace swarm::test;

TEST_CASE("Simple DI", "[di]") {
    
    ObjectInject{}.launch();
    REQUIRE(ObjectToInject::count_ == 1);
    REQUIRE(ObjectToInject::launch_ == 1);
    REQUIRE(ApplicationObjectToInject::count_ == 1);
    REQUIRE(ApplicationObjectToInject::launch_ == 1);
    
    ObjectInject{}.launch();
    REQUIRE(ObjectToInject::count_ == 2);
    REQUIRE(ObjectToInject::launch_ == 2);
    REQUIRE(ApplicationObjectToInject::count_ == 1);
    REQUIRE(ApplicationObjectToInject::launch_ == 2);
}
