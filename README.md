PoC B REQUIREMENTS — Encoded-Segment Circular Buffer (30-Second Prebuffer)
1. Overall Objective
Implement a pre-recording buffer that continuously captures, encodes, segments, and stores the last 30 seconds of video (and audio if enabled).
 When a trigger occurs, the system assembles the last 30 seconds into a single playable clip.

2. Architecture Requirements
2.1 Continuous Encoding
The system must continuously encode the camera stream into a compressed format.


Recommended format:


Video: H.264


Audio: AAC (optional)


Container per segment: MPEG-TS (preferred for easy concatenation)


2.2 Segmented Recording
Instead of creating a single 30-second file, the system must break the stream into short, fixed-duration segments.


Segment duration: 1 second (acceptable range: 1–3s).


Each segment must be a standalone, decodable file starting with a keyframe.


2.3 Circular Storage
The system must only keep the latest 30 seconds of segments on storage.


Must implement a circular buffer:


When new segments arrive, oldest segments are deleted.


Segment count = 30 / segment_duration.


2.4 Durability and Crash Safety
Segments must be written in a crash-safe manner:


Write to temporary file (*.tmp)


Sync file to disk


Rename to final filename atomically


Sync containing directory


Loss of power must not corrupt previously completed segments.


Worst-case data loss allowed: < 1 segment (i.e., up to ~1 second).



3. RAM Cache Requirements
3.1 Purpose of RAM Cache
Reduce trigger latency.


Avoid reading a partially-written segment from disk.


Provide instant access to the newest finished segment.


3.2 Size
The system must cache at least the last completed segment in RAM.


Optional: cache last 1–3 seconds depending on RAM budget.


3.3 Storage Mode
Store encoded bytes, not raw frames.



4. Trigger Handling Requirements
4.1 Trigger Input
Trigger can be:


Hardware button


Software event


Sensor event (future work)


4.2 Prebuffer Assembly
Upon trigger:
The system must gather the last 30 seconds of segments.


Sources:


RAM cache (for newest segment(s))


Disk segments (for older ones)


4.3 Output Clip
Output must be a continuous playable clip (TS or MP4).


Two acceptable approaches:


TS output: direct file concatenation


MP4 output: remux TS segments into MP4 (no re-encoding)


4.4 Performance
Total time from trigger to preroll output:


Target: < 300 ms


Maximum: < 1 s



5. Storage Management Requirements
5.1 Directory Structure
All segments must be stored under:
 ./segments/segment_XXXXX.ts


Filenames must be sequential and zero-padded.


5.2 Segment Retention
Maintain exactly the number of segments required for the prebuffer:


If 1s segments → keep last 30 files


If 2s segments → keep last 15 files


5.3 Disk Usage
At 2–4 Mbps (720p):


1s segment ≈ 250–500 KB


30s ≈ 7.5–15 MB total


Recommended to reserve 25 MB of disk space for safety.


5.4 Safe Removal of Old Segments
Delete oldest segments only after:


New segment has been successfully written


Metadata/index updated



6. Index & Metadata Requirements
6.1 Segment Index
Maintain an in-memory index storing:
Filename


Sequence number


Start timestamp


Duration


Must support:
Fetch “last N segments”


Fetch segments covering a timestamp range


6.2 Timestamp Handling
Every segment must have an accurate wall-clock timestamp.


Must also store monotonic timestamp to handle clock changes.


6.3 Metadata (Optional for PoC)
GPS, IMU, accelerometer metadata may be added later.


For now, minimal metadata: timestamps only.



7. Video Encoding Requirements
7.1 Bitrate
Select bitrate based on quality vs. storage:


720p → 2–4 Mbps typical.


7.2 Keyframe Interval
Keyframe interval must equal segment duration:


For 1s segments at 30fps: key-int-max = 30


Ensures each segment is independently decodable.


7.3 Latency Settings
Encoder must run in low-latency / zerolatency mode.



8. Concurrency Requirements
8.1 Threads Needed
Capture/Encoding: GStreamer pipeline thread(s)


Segment Handler: file writer thread


Directory Watcher (or sink callback)


Trigger Handler


Cleanup Thread (optional)


8.2 Thread Safety
Index must be mutex-protected.


RAM cache mutex-protected.


Ensure no race between file writer and trigger handler.



9. Output Requirements
9.1 Final Prebuffer File
Must output:


preroll.ts (TS concatenation)


or preroll.mp4 (if remux required)


9.2 Playback Compatibility
TS must be playable by:


VLC


ffplay


GStreamer gst-play-1.0


MP4 must be playable by any standard player.



10. Testing Requirements
10.1 Functional Tests
Verify exactly 30 seconds of buffer is maintained.


Trigger while recording → output correct 30s clip.


Trigger immediately after start (<30s) → output available segment duration.


10.2 Crash Tests
Simulate:
Power cut during segment write


OS kill of application


Disk full condition
 System must:


Lose at most 1 second


Never corrupt previous segments


Recover cleanly on restart


10.3 Performance Tests
Measure trigger-to-output latency


Measure disk write speed


Measure CPU load while encoding and segmenting



11. Non-Functional Requirements
11.1 Portability
Runs on Linux (desktop or embedded)


Should support hardware encoders if available (e.g., V4L2 H.264 encoders)


11.2 Extensibility
Future features:
Audio


IMU/GPS metadata


Per-segment cryptographic signatures


Encrypted prebuffer storage


11.3 Maintainability
Clear directory structure


Modular components: encoder, segmenter, index, trigger output



12. Summary (TL;DR)
Encode video continuously.


Produce 1-second H.264 TS segments.


Store only the last 30 files = 30 seconds.


Use atomic write (tmp → sync → rename).


Keep last segment in RAM.


On trigger:


Retrieve last 30 segments


Concat/remux to a final clip


Output within <300 ms.

