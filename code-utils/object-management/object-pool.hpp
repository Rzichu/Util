#pragma once

#include <vector>
#include <utility>
#include <memory>

namespace g_utils {
    namespace obj_management {
        // NOT THREAD SAFE
        template<typename _OBJ_TYPE>
        class ObjectPool {
            typedef std::shared_ptr<_OBJ_TYPE> ObjPtr;

        public:
            void reserve(std::size_t p_size) { this->m_Objects.reserve(p_size); }

            void fill() {
                for (auto &obj : this->m_Objects) {
                    if (obj.first == nullptr) {
                        obj.first = std::make_shared<_OBJ_TYPE>();
                    }
                }
            }

            void resize(std::size_t p_size) { this->m_Objects.resize(p_size); }

            void shrink() { this->m_Objects.shrink_to_fit(); }
            
            ObjPtr getObject() {
                for (auto &obj : this->m_Objects) {
                    if (obj.second == false) {
                        obj.second = true;
                        return obj.first;
                    }
                }
                return nullptr;
            }
            
            void freeObject(const ObjPtr &p_obj) {
                if (p_obj) {
                    for (auto &obj : this->m_Objects) {
                        if (*obj.first == *p_obj) {
                            obj.second = false;
                        }
                    }
                }
            }

        public:
            ObjectPool() = default;

            virtual ~ObjectPool() = default;

            ObjectPool(const ObjectPool &p_copy) = default;
            ObjectPool &operator=(const ObjectPool &p_copy) = default;
            
            ObjectPool(ObjectPool &&p_move) = default;
            ObjectPool &operator=(ObjectPool &&p_move) = default;
        
        protected:
            std::vector<std::pair<ObjPtr>, bool> m_Objects;
        };
    }
}