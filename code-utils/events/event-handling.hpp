#pragma once

#include <memory>

namespace g_utils {
    namespace eventsystem {
        template<typename TSender, typename TArgument>
        class EventDelegate {
        private:
            struct Callable {
                virtual ~Callable() {}
                virtual void Call(TSender* p_sender, TArgument* p_argument) = 0;
            };

            template<typename TClass>
            struct CallableImpl : public Callable {
                TClass* _instance;
                void (TClass::*_method)(TSender*, TArgument*);

                CallableImpl(TClass* p_instance, void (TClass::*p_method)(TSender*, TArgument*))
                : _instance(p_instance), _method(p_method) {}

                void Call(TSender* p_sender, TArgument* p_argument) {
                    (_instance->*_method)(p_sender, p_argument);
                }
            };

        protected:
            std::shared_ptr<Callable> _callable; // smart pointer

        public:
            template<typename TClass>
            EventDelegate(const TClass* p_instance, void (TClass::*p_method)(TSender* p_sender, TArgument* p_argument))
                : _callable(new CallableImpl<TClass>(p_instance, p_method)) {}

            EventDelegate()
                : _callable(0) {}

            ~EventDelegate() {
            }

            void operator()(TSender* p_sender, TArgument* p_argument) {
                if (_callable) {
                    _callable->Call(p_sender, p_argument);
                }
            }
        };

        /* USAGE:
        
            class Button {
            public:
                typedef EventDelegate<Button, ButtonClickArgs> ClickEvent;
                ClickEvent OnClick;

            protected:
                RaiseClick() {
                    ButtonClickArgs args(...);
                    OnClick(this, &args)
                }
            };

            class App {
            public:
                App() {
                    // Here the smart pointer ensures that the Callable isn't
                    // destroyed when the Button::ClickEvent object on the stack 
                    // goes out of scope
                    g_button->OnClick = Button::ClickEvent(this, &App::ClickHandler)
                }

                ~App() {
                    g_button->OnClick = Button::ClickEvent();
                }
            
            protected:
                void ClickHandler(Button* button, ButtonClickArgs* args) {
                    ...
                }
            };

        */

    }
}