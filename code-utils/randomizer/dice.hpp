#pragma once

#include <random>

namespace g_utils {
    namespace random {
        class DiceBase {
        public:
            inline virtual short roll() {
                return this->operator()();
            }

            inline virtual short operator()() {
                return m_RandDist(m_RandGen);
            }

        protected:
            DiceBase() = delete;

            DiceBase(short p_min, short p_max)
                : m_RandGen(this->m_RandDevice())
                , m_RandDist(p_min, p_max)
                {}
            
            virtual ~DiceBase() = default;

        protected:
            std::random_device m_RandDevice;
            std::mt19937 m_RandGen;
            std::uniform_int_distribution<short> m_RandDist;
        };

        class D3 final : public DiceBase {
        public:
            D3()
                : DiceBase::DiceBase(1, 3)
                {}
        };

        class D4 final : public DiceBase {
        public:
            D4()
                : DiceBase::DiceBase(1, 4)
                {}
        };

        class D5 final : public DiceBase {
        public:
            D5()
                : DiceBase::DiceBase(1, 5)
                {}
        };

        class D6 final : public DiceBase {
        public:
            D6()
                : DiceBase::DiceBase(1, 6)
                {}
        };

        class D7 final : public DiceBase {
        public:
            D7()
                : DiceBase::DiceBase(1, 7)
                {}
        };

        class D8 final : public DiceBase {
        public:
            D8()
                : DiceBase::DiceBase(1, 8)
                {}
        };

        class D9 final : public DiceBase {
        public:
            D9()
                : DiceBase::DiceBase(0, 9)
                {}
            
            inline short rollTens() {
                return (this->roll() * 10);
            }
        };

        class D12 final : public DiceBase {
        public:
            D12()
                : DiceBase::DiceBase(1, 12)
                {}
        };

        class D16 final : public DiceBase {
        public:
            D16()
                : DiceBase::DiceBase(1, 16)
                {}
        };

        class D20 final : public DiceBase {
        public:
            D20()
                : DiceBase::DiceBase(1, 20)
                {}
        };

        class D24 final : public DiceBase {
        public:
            D24()
                : DiceBase::DiceBase(1, 24)
                {}
        };

        class D30 final : public DiceBase {
        public:
            D30()
                : DiceBase::DiceBase(1, 30)
                {}
        };

        class D60 final : public DiceBase {
        public:
            D60()
                : DiceBase::DiceBase(1, 60)
                {}
        };

        class D100 final : public DiceBase {
        public:
            D100()
                : DiceBase::DiceBase(1, 100)
                {}
        };
    }
}