#ifndef _RECORDER_H_
#define _RECORDER_H_

#include <memory>
#include <vector>
#include <unordered_map>

#include <Global\Global.h>
#include <Operation\Operation.h>
#include "RecordedOperation.h"

class Recorder
{
public:
	Recorder();
	bool IsRecording() const;
	bool IsRecordingAborted() const;
	const Address GetRecordingStartAddress() const;
	void StopRecording();
	void AbortRecording();
	void StartRecording(Address startAddress);
	void AddToRecording(const RecordedOperation& recordedOperation);
	const std::vector<RecordedOperation>& GetRecordedOperations() const;
private:
	std::vector<RecordedOperation> recordedOperations_;
	Address recordingStartAddress_;
	bool isRecording_;
	bool isAborted_;
	static const int MAX_RECORDED_OPERATIONS_COUNT;
};

#endif