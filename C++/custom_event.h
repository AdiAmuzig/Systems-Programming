//
// Created by adi.amuzig on 10/01/2021.
//

#ifndef HW3_CUSTOM_EVENT_H
#define HW3_CUSTOM_EVENT_H

#include "base_event.h"

namespace mtm {
    template<class CanRegister>
    class CustomEvent : public BaseEvent {
        CanRegister can_register;
    public:
        CustomEvent(const DateWrap &date,
                    const std::string &name,
                    CanRegister can_register);

        void registerParticipant(const int &student) override;

        BaseEvent *clone() const override;
    };
}

namespace mtm {
    template<class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const DateWrap &date,
                                          const std::string &name,
                                          CanRegister can_register) :
            BaseEvent(date, name),
            can_register(can_register) {
    }

    template<class CanRegister>
    void CustomEvent<CanRegister>::registerParticipant(const int &student) {
        checkLegalStudent(student);
        if (can_register(student) == false) {
            throw RegistrationBlocked();
        }
        BaseEvent::registerParticipant(student);
    }

    template<class CanRegister>
    BaseEvent *CustomEvent<CanRegister>::clone() const {
        CustomEvent *new_custom_event =
                new CustomEvent(getDate(), getName(), can_register);
        new_custom_event->participatingStudents = participatingStudents;
        return new_custom_event;
    }
}

#endif //HW3_CUSTOM_EVENT_H
