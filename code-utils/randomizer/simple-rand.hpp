#pragma once

#include <random>

namespace g_utils {
    namespace random {
        class RandomBool {
        public:
            RandomBool()
                : m_RandGen(this->m_RandDevice())
                {}
            
            RandomBool(double p_probability)
                : m_RandGen(this->m_RandDevice())
                , m_RandDist(p_probability)
                {}
            
            inline bool get() {
                return this->operator()();
            }
            
            inline bool get(std::bernoulli_distribution &p_dist) {
                return this->operator()(p_dist);
            }

            inline bool operator()() {
                return this->m_RandDist(m_RandGen);
            }

            inline bool operator()(std::bernoulli_distribution &p_dist) {
                return p_dist(m_RandGen);
            }

        private:
            std::random_device m_RandDevice;
            std::mt19937 m_RandGen;
            std::bernoulli_distribution m_RandDist;
        };
        
        template<typename _IntType>
        class RandomInt {
        public:
            RandomInt()
                : m_RandGen(this->m_RandDevice())
                {}

            RandomInt(_IntType p_min, _IntType p_max)
                : m_RandGen(this->m_RandDevice())
                , m_RandDist(p_min, p_max)
                {}

            inline _IntType get() {
                return this->operator()();
            }

            inline _IntType get(std::uniform_int_distribution<_IntType> &p_dist) const {
                return this->operator()(p_dist);
            }

            inline _IntType operator()() {
                return this->m_RandDist(m_RandGen);
            }

            inline _IntType operator()(std::uniform_int_distribution<_IntType> &p_dist) const {
                return p_dist(m_RandGen);
            }

        private:
            std::random_device m_RandDevice;
            std::mt19937 m_RandGen;
            std::uniform_int_distribution<_IntType> m_RandDist;
        };

        template<typename _RealType>
        class RandomReal {
        public:
            RandomReal()
                : m_RandGen(this->m_RandDevice())
                {}

            RandomReal(_RealType p_min, _RealType p_max)
                : m_RandGen(this->m_RandDevice())
                , m_RandDist(p_min, p_max)
                {}

            inline _RealType get() {
                return this->operator()();
            }

            inline _RealType get(std::uniform_real_distribution<_RealType> &p_dist) const {
                return this->operator()(p_dist);
            }

            inline _RealType operator()() {
                return this->m_RandDist(m_RandGen);
            }

            inline _RealType operator()(std::uniform_real_distribution<_RealType> &p_dist) const {
                return p_dist(m_RandGen);
            }

        private:
            std::random_device m_RandDevice;
            std::mt19937 m_RandGen;
            std::uniform_real_distribution<_RealType> m_RandDist;
        };
    }
}