# ModbusMaster CHANGELOG

## [v1.0.0](https://github.com/4-20ma/ModbusMaster/tree/v1.0.0) (2016-09-11)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.11.0...v1.0.0)

**Implemented enhancements:**

- Add continuous integration testing with travis [\#55](https://github.com/4-20ma/ModbusMaster/issues/55)
- Add Code of Conduct [\#54](https://github.com/4-20ma/ModbusMaster/issues/54)
- Create PULL\_REQUEST\_TEMPLATE [\#49](https://github.com/4-20ma/ModbusMaster/issues/49)
- Create ISSUE\_TEMPLATE [\#48](https://github.com/4-20ma/ModbusMaster/issues/48)
- Change license to Apache 2.0 [\#45](https://github.com/4-20ma/ModbusMaster/issues/45)
- Set \_\_MODBUSMASTER\_DEBUG\_\_ to 0 by default [\#35](https://github.com/4-20ma/ModbusMaster/issues/35)
- Pass Stream object instead of integer reference [\#17](https://github.com/4-20ma/ModbusMaster/issues/17)
- Add LICENSE, convert project to Apache 2.0 [\#67](https://github.com/4-20ma/ModbusMaster/pull/67) ([4-20ma](https://github.com/4-20ma))
- Add example sketch for half-duplex RS485 [\#66](https://github.com/4-20ma/ModbusMaster/pull/66) ([kintel](https://github.com/kintel))
- Add continuous integration testing with Travis CI [\#63](https://github.com/4-20ma/ModbusMaster/pull/63) ([4-20ma](https://github.com/4-20ma))
- Add initial .travis.yml configuration [\#62](https://github.com/4-20ma/ModbusMaster/pull/62) ([4-20ma](https://github.com/4-20ma))
- Add CODE\_OF\_CONDUCT [\#56](https://github.com/4-20ma/ModbusMaster/pull/56) ([4-20ma](https://github.com/4-20ma))
- Add initial PULL\_REQUEST\_TEMPLATE [\#53](https://github.com/4-20ma/ModbusMaster/pull/53) ([4-20ma](https://github.com/4-20ma))
- Add initial ISSUE\_TEMPLATE [\#50](https://github.com/4-20ma/ModbusMaster/pull/50) ([4-20ma](https://github.com/4-20ma))
- Add preTransmission\(\), postTransmission\(\) for half-duplex [\#44](https://github.com/4-20ma/ModbusMaster/pull/44) ([kintel](https://github.com/kintel))
- Disable \_\_MODBUSMASTER\_DEBUG\_\_ mode by default [\#43](https://github.com/4-20ma/ModbusMaster/pull/43) ([kintel](https://github.com/kintel))
- Add STYLE coding style guide [\#29](https://github.com/4-20ma/ModbusMaster/pull/29) ([4-20ma](https://github.com/4-20ma))

**Closed issues:**

- Fix documentation references in ModbusMaster.h, .cpp [\#69](https://github.com/4-20ma/ModbusMaster/issues/69)
- Clean up template wording [\#64](https://github.com/4-20ma/ModbusMaster/issues/64)
- Add Label section to CONTRIBUTING [\#60](https://github.com/4-20ma/ModbusMaster/issues/60)
- Update README contact information [\#58](https://github.com/4-20ma/ModbusMaster/issues/58)

**Merged pull requests:**

- Clean up ISSUE/PULL\_REQUEST templates [\#65](https://github.com/4-20ma/ModbusMaster/pull/65) ([4-20ma](https://github.com/4-20ma))
- Add label guidance to CONTRIBUTING [\#61](https://github.com/4-20ma/ModbusMaster/pull/61) ([4-20ma](https://github.com/4-20ma))
- Update README contact information [\#59](https://github.com/4-20ma/ModbusMaster/pull/59) ([4-20ma](https://github.com/4-20ma))
- Add email address to CODE\_OF\_CONDUCT [\#57](https://github.com/4-20ma/ModbusMaster/pull/57) ([4-20ma](https://github.com/4-20ma))
- Clarify instructions in ISSUE\_TEMPLATE [\#52](https://github.com/4-20ma/ModbusMaster/pull/52) ([4-20ma](https://github.com/4-20ma))
- Add ISSUE\_TEMPLATE title reqs, separator lines [\#51](https://github.com/4-20ma/ModbusMaster/pull/51) ([4-20ma](https://github.com/4-20ma))

## [v0.11.0](https://github.com/4-20ma/ModbusMaster/tree/v0.11.0) (2015-05-22)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.10.3...v0.11.0)

**Implemented enhancements:**

- Update architecture switch to match Arduino convention [\#27](https://github.com/4-20ma/ModbusMaster/issues/27)
- Request timeout is impatient [\#3](https://github.com/4-20ma/ModbusMaster/issues/3)
- Update architecture switch [\#28](https://github.com/4-20ma/ModbusMaster/pull/28) ([4-20ma](https://github.com/4-20ma))

## [v0.10.3](https://github.com/4-20ma/ModbusMaster/tree/v0.10.3) (2015-05-22)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.10.2...v0.10.3)

**Closed issues:**

- Inconsistent Doxygen comments [\#25](https://github.com/4-20ma/ModbusMaster/issues/25)
- Replace C macros with inline functions [\#18](https://github.com/4-20ma/ModbusMaster/issues/18)

**Merged pull requests:**

- Adjust doxygen comments to be consistent [\#26](https://github.com/4-20ma/ModbusMaster/pull/26) ([4-20ma](https://github.com/4-20ma))
- Replace C macros w/inline functions [\#24](https://github.com/4-20ma/ModbusMaster/pull/24) ([4-20ma](https://github.com/4-20ma))

## [v0.10.2](https://github.com/4-20ma/ModbusMaster/tree/v0.10.2) (2015-05-22)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.9.1...v0.10.2)

**Implemented enhancements:**

- Implement CRC16 for SAM3X8E microprocessor [\#11](https://github.com/4-20ma/ModbusMaster/pull/11) ([4-20ma](https://github.com/4-20ma))
- Add rx flush, change response timeout to 2000 ms [\#10](https://github.com/4-20ma/ModbusMaster/pull/10) ([agprimatic](https://github.com/agprimatic))

**Fixed bugs:**

- Fix documentation build error [\#23](https://github.com/4-20ma/ModbusMaster/pull/23) ([4-20ma](https://github.com/4-20ma))
- Work around HardwareSerial for SAM3 micro [\#12](https://github.com/4-20ma/ModbusMaster/pull/12) ([4-20ma](https://github.com/4-20ma))

**Merged pull requests:**

- Update pointers to match C++ convention [\#22](https://github.com/4-20ma/ModbusMaster/pull/22) ([4-20ma](https://github.com/4-20ma))
- Rename markdown file extensions [\#21](https://github.com/4-20ma/ModbusMaster/pull/21) ([4-20ma](https://github.com/4-20ma))

## [v0.9.1](https://github.com/4-20ma/ModbusMaster/tree/v0.9.1) (2013-01-02)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.9...v0.9.1)

## [v0.9](https://github.com/4-20ma/ModbusMaster/tree/v0.9) (2011-12-27)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.8...v0.9)

## [v0.8](https://github.com/4-20ma/ModbusMaster/tree/v0.8) (2011-11-09)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.7...v0.8)

## [v0.7](https://github.com/4-20ma/ModbusMaster/tree/v0.7) (2010-02-10)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.6...v0.7)

## [v0.6](https://github.com/4-20ma/ModbusMaster/tree/v0.6) (2010-02-05)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.5...v0.6)

## [v0.5](https://github.com/4-20ma/ModbusMaster/tree/v0.5) (2010-01-30)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.4...v0.5)

## [v0.4](https://github.com/4-20ma/ModbusMaster/tree/v0.4) (2010-01-30)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.3...v0.4)

## [v0.3](https://github.com/4-20ma/ModbusMaster/tree/v0.3) (2010-01-29)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.2...v0.3)

## [v0.2](https://github.com/4-20ma/ModbusMaster/tree/v0.2) (2010-01-26)
[Full Changelog](https://github.com/4-20ma/ModbusMaster/compare/v0.1...v0.2)

## [v0.1](https://github.com/4-20ma/ModbusMaster/tree/v0.1) (2010-01-25)


\* *This Change Log was automatically generated by [github_changelog_generator](https://github.com/skywinder/Github-Changelog-Generator)*