#include "KCCISchoolNet.h"

#ifndef POPULATELISTS_H
#define POPULATELISTS_H

void PopulateStationList(LinkedList &, CComboBox &);
void PopulateWebCamList(LinkedList &, CComboBox &);

int FindDefaultStation(LinkedList &);
void FindStationID(int, LinkedList &, CString & );
KCCISchoolNetData * FindData(const char * , LinkedList & );

#endif