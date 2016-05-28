#include "Recorder.h"

Recorder::Recorder() :
	isRecording_(false),
	isAborted_(false),
	recordingStartAddress_(0)
{}

bool Recorder::IsRecording() const
{
	return isRecording_;
}

bool Recorder::IsRecordingAborted() const
{
	return isAborted_;
}

const Address Recorder::GetRecordingStartAddress() const
{
	return recordingStartAddress_;
}

void Recorder::StopRecording()
{
	isRecording_ = false;
	isAborted_ = false;
}

void Recorder::AbortRecording()
{
	isRecording_ = false;
	isAborted_ = true;
}

void Recorder::StartRecording(Address startAddress)
{
	isRecording_ = true;
	isAborted_ = false;
	recordingStartAddress_ = startAddress;
	recordedOperations_.clear();
}

void Recorder::AddToRecording(const RecordedOperation & recordedOperation)
{
	recordedOperations_.push_back(recordedOperation);
}

const std::vector<RecordedOperation>& Recorder::GetRecordedOperations() const
{
	return recordedOperations_;
}


