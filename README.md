# CATS Readme

CATS* is a simple proof-of-concept application, designed to demonstrate a methodology for replacing sensitive form data with semantically equivalent data, assuming triggers from a HIDS or other threat detection tool, for the purposes of simultaneous data protection and counter-intelligence/threat-actor tracking.

Compiling:
- Requires Boost libraries (https://www.boost.org) (initially developed with with Boost 1.4x).
- After cloning, run:

$ cd CATS/

$ make

After compiling, run "cats --help" for usage info.

CATS takes an input argument of the source directory through the --source flag. It opens that directory and reads in the filenames. It then reads in each file and each line of each file and passes the line to a parsing function which then calls various scanners to identify the data types to be modified. The scanners are designed to be modular in order to easily add additional data types.

Todo/future ideas:
- Data identification, tagging, and storage.
- Detection algorithm for finding and associating tagged data.
- Fix PoC hardcoding and add config files.
- Integrate with threat dection tool.
- Add lots of data type modules.
- Design modules to not require re-compile.
- Work on form methodology. 
- OCR
- MIME Type matching rather than just text. (Possible application for steganographic tagging?)
- Data identifcation is regex based. Possible application for machine learning?

*Wrote this quite a while ago. Don't remember what the acronym meant :-).



