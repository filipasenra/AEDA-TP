
#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include <list>
#include <stack>
#include "Doctor.h"


class Hospital {
  list<Doctor> doctors;
  list<stack<Patient> > letterTray;
  unsigned trayCapacity;
public:
  Hospital(unsigned trayC=20);
  void addDoctor(const Doctor &d1);
  list<Doctor> getDoctors() const;
  void addTrays(stack<Patient> tray1);
  list<stack<Patient> > getTrays() const;

  void sortDoctors();
  unsigned numPatients(string medicalSpecialty) const;
  bool addDoctor(unsigned codM1, string medicalSpecialty1);
  queue<Patient> removeDoctor(unsigned codM1);
  bool putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1);
  void processPatient(unsigned codM1);
  unsigned removePatients(unsigned codP1);

  class DoctorInexistent {};
};


#endif /* HOSPITAL_H_ */
