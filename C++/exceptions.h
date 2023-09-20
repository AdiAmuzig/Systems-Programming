//
// Created by adi.amuzig on 09/01/2021.
//

#ifndef HW3_EXCEPTIONS_H
#define HW3_EXCEPTIONS_H

namespace mtm {
    class Exception : public std::exception {
    };

    class NegativeDays : public Exception {
    };

    class InvalidDate : public Exception {
    };

    class InvalidStudent : public Exception {
    };

    class AlreadyRegistered : public Exception {
    };

    class RegistrationBlocked : public Exception {
    };

    class NotRegistered : public Exception {
    };

    class AlreadyInvited : public Exception {
    };

    class NotSupported : public Exception {
    };

    class DateMismatch : public Exception {
    };

    class InvalidNumber : public Exception {
    };

    class InvalidInterval : public Exception {
    };

    class EventAlreadyExists : public Exception {
    };

    class EventDoesNotExist : public Exception {
    };
}

#endif //HW3_EXCEPTIONS_H
