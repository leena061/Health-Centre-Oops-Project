#ifndef APPOINTMENT_DATA_H
#define APPOINTMENT_DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Appointment {
    std::string id;
    std::string patientId;
    std::string doctorId;
    std::string date;
    std::string time;
};

class AppointmentData {
public:
    void addAppointment(const Appointment& appointment);
    void editAppointment(const std::string& id, const std::string& date, const std::string& time);
    std::vector<Appointment> getAppointments();
    void loadAppointments();
    void saveAppointments();
private:
    std::vector<Appointment> appointments_;
};

extern AppointmentData appointmentData; // declare appointmentData as a global object

#endif  // APPOINTMENT_DATA_H