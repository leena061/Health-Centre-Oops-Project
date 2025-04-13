#include "appointment_data.h"

AppointmentData appointmentData;
void AppointmentData::addAppointment(const Appointment& appointment) {
    appointments_.push_back(appointment);
}

void AppointmentData::editAppointment(const std::string& patientId, const std::string& date, const std::string& time) {
    for (auto& appointment : appointments_) {
        if (appointment.patientId == patientId) {
            appointment.date = date;
            appointment.time = time;
            return;
        }
    }
}

std::vector<Appointment> AppointmentData::getAppointments() {
    return appointments_;
}

void AppointmentData::loadAppointments() {
    std::ifstream file("appointments.txt");
    if (!file) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Appointment appointment;
        std::getline(ss, appointment.id, ',');
        std::getline(ss, appointment.patientId, ',');
        std::getline(ss, appointment.doctorId, ',');
        std::getline(ss, appointment.date, ',');
        std::getline(ss, appointment.time, ',');
        appointments_.push_back(appointment);
    }
    file.close();
}

void AppointmentData::saveAppointments() {
    std::ofstream file("appointments.txt");
    for (const auto& appointment : appointments_) {
        file << appointment.id << "," << appointment.patientId << "," << appointment.doctorId << "," << appointment.date << "," << appointment.time << std::endl;
    }
    file.close();
}