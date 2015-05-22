## [v0.10.3 (2015-05-22)](/4-20ma/ModbusMaster/tree/v0.10.3)
- Adjust doxygen comments to be consistent
- Replace C macros w/inline functions
- Update library.properties to conform to others
- Adjust README links to use absolute URLs

---
## [v0.10.2 (2015-05-21)](/4-20ma/ModbusMaster/tree/v0.10.2)
- Update documentation after resolving doc build err
- Fix documentation build error
- Update library.properties
- Add README badges for tag, license
- Update README
    - Replace **Heading** with Heading followed by ------- line for cleaner Markdown syntax
    - Update Arduino version note to 1.6
    - Fix nanoline URL
- Remove deprecation note from README
- Update pointers to match C++ convention
- Rename markdown file extensions

---
## [v0.10.1 (2015-05-20)](/4-20ma/ModbusMaster/tree/v0.10.1)
- Update Rakefile to commit Doxyfile, reference
- Version bump to v0.10.0

---
## [v0.10.0 (2015-05-20)](/4-20ma/ModbusMaster/tree/v0.10.0)
- Update Rakefile to update library.properties
- Add library.properties file to describe library
- Add .ruby-* to manage versions via rvm or rbenv
- Add Gemfile to manage dependencies via Bundler
- Update .gitignore to exclude Gemfile.lock
- Work around HardwareSerial for SAM3 micro
    - add #ifdefs to check for presence of AVR or ARM chipset (use HardwareSerial for AVR and UARTClass for ARM)
    - change MBSerial to pointer and update all references to use -> notation instead of . notation
- Implement CRC16 for SAM3X8E microprocessor
    - renamed _crc16_update to crc16_update to minimize confusion with AVR function in util/crc16.h
    - added C version of crc16 and removed extraneous version of crc16 functions
- Add end-of-life note to README
- Add auto-generated pdf documentation for v0.9.1
- Remove pdf documentation for versions 0.6, 0.7
- Add pdf documentation for versions 0.6, 0.7
- Remove unnecessary require 'fileutils'
- Add auto-generated pdf documentation
- Define PROJECT_BRIEF tag in Doxyfile
- Add pdf generation to prepare:documentation
- Add doc/README.txt

---
## [v0.9.1 (2013-01-02)](/4-20ma/ModbusMaster/tree/v0.9.1)
- Add Rakefile to manage prepare/release process
- Add .gitignore to skip doc/html, doc/latex files
- Add Doxyfile to repo
- Update copyright year
- Update email address
- Fix references to repo
- Move history to separate file
- Update README copyright, email

---
## [v0.9 (2011-12-04)](/4-20ma/ModbusMaster/tree/v0.9)
- Add support for Arduino 1.0

---
## [v0.8 (2011-11-09)](/4-20ma/ModbusMaster/tree/v0.8)
- Add support for ATmega2560

---
## [v0.7 (2010-02-09)](/4-20ma/ModbusMaster/tree/v0.7)
- Modified capitalization of functions to match Arduino style where first letter is lower-case

---
## [v0.6 (2010-02-04)](/4-20ma/ModbusMaster/tree/v0.6)
- Added documentation via Doxygen comments, modified methods used to get/set storage buffers

---
## [v0.5 (2010-01-30)](/4-20ma/ModbusMaster/tree/v0.5)
- Added ability to select serial port 0..3, modified methods used to get/set storage arrays, miscellaneous bug fixes

---
## [v0.3 (2010-01-29)](/4-20ma/ModbusMaster/tree/v0.3)

---
## [v0.2 (2010-01-25)](/4-20ma/ModbusMaster/tree/v0.2)

---
## [v0.1 (2010-01-24)](/4-20ma/ModbusMaster/tree/v0.1)
- Initial public release
