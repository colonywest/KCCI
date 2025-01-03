#include "stdafx.h"

#include "LinkedList.h"
#include "KCCISchoolNet.h"
#include "Registry.h"

void PopulateStationList(LinkedList & stationList, CComboBox & listBox)
{
	int x; KCCIStationList * pNode;

	listBox.ResetContent();

	for(x = 0; x < stationList.size(); x++)
	{
		pNode = (KCCIStationList *)stationList.elementAt(x);
		listBox.AddString(pNode->stationName);
	}
}

void PopulateWebCamList(LinkedList & cameraList, CComboBox & listBox)
{
	int x; KCCICameraList * pNode;

	listBox.ResetContent();

	for(x = 0; x < cameraList.size(); x++)
	{
		pNode = (KCCICameraList *)cameraList.elementAt(x);
		listBox.AddString(pNode->stationName);
	}
}

int FindDefaultStation(LinkedList & input)
{
	CString defaultStationID;
	KCCIStationList * pNode;

	/* Read the default station from the registry */

	GetDefaultStation(defaultStationID);

	/* Try to find it in the linked list */

	for(int x = 0; x < input.size(); x++)
	{
		pNode = (KCCIStationList *)input.elementAt(x);
		if(pNode->stationID.compareToIgnoreCase(defaultStationID) == 0) break;
	}

	if(x >= input.size()) x = 0;
	return x;
}

void FindStationID(int index, LinkedList & input, CString & output)
{
	KCCIStationList * pNode = (KCCIStationList *)input.elementAt(index);
	if(pNode == NULL) return;
	output = pNode->stationID;
	return;
}

KCCISchoolNetData * FindData(const char * stationID, LinkedList & input)
{
	KCCISchoolNetData * dataNode; int x;

	for(x = 0; x < input.size(); x++)
	{
		dataNode = (KCCISchoolNetData * )input.elementAt(x);
		if(stricmp(dataNode->stationID, stationID) == 0) return dataNode;
	}

	return NULL;
}