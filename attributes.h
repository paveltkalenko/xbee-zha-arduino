#ifndef _ZHA_ATTRIBUTES_H_
#define _ZHA_ATTRIBUTES_H_

#define ZHA_TYPE_NULL   0x00
#define ZHA_TYPE_BOOL   0x10
#define ZHA_TYPE_UINT8  0x20
#define ZHA_TYPE_UINT16 0x21
#define ZHA_TYPE_UINT24 0x22
#define ZHA_TYPE_UINT32 0x23
#define ZHA_TYPE_UINT40 0x24
#define ZHA_TYPE_UINT48 0x25
#define ZHA_TYPE_UINT56 0x26
#define ZHA_TYPE_UINT64 0x27
#define ZHA_TYPE_8BIT_BITMAP      0x18
#define ZHA_TYPE_8BIT_ENUMERATION 0x30
#define ZHA_TYPE_CHARACTER_STRING 0x42

class Attribute { 
public:
  Attribute(uint16_t attrId, uint8_t datatype, uint64_t value) {
    _attrId = attrId;
    _datatype = datatype;
    _value = value;
    _reporting = false;
    _unreported = false;
  };
  Attribute(uint16_t attrId, uint8_t datatype, String value) {
    _attrId = attrId;
    _datatype = datatype;
    _strValue = value;
    _reporting = false;
    _unreported = false;
  };
  uint16_t getAttrId() { return _attrId; }
  uint8_t  getValueUINT8() { return (uint8_t)_value; }
  bool     getValueBool() { return (bool)_value; }
  uint8_t  getAttrType() { return _datatype; }
  bool     needsReporting() { return _reporting && _unreported; } 
  void     markReported() { _unreported = false; }
  void set(uint64_t value) {
    _value = value;
    if (_reporting) {
      _unreported = true;
    }
  }
 
  uint16_t getAttrSize() {
    switch(_datatype) {
      case ZHA_TYPE_NULL:
        return 0;
        break;
      case ZHA_TYPE_BOOL:
      case ZHA_TYPE_UINT8:
      case ZHA_TYPE_8BIT_ENUMERATION:
      case ZHA_TYPE_8BIT_BITMAP:
        return 1;
        break;
      case ZHA_TYPE_UINT16:
        return 2;
        break;
      default:
        return 0;
    }
  }
  
  uint8_t configureReporting(uint8_t datatype, uint16_t minimum_interval, uint16_t maximum_interval, uint8_t reportable_change, uint16_t timeout_period) {
    _last_reported = 0;
    _minimum_reporting_interval = minimum_interval;
    _maximum_reporting_interval = maximum_interval;
    _reportable_change = reportable_change;
    _timeout_period = timeout_period;
    _reporting = true;  
  }
private: 
  uint8_t _datatype;
  uint16_t _attrId;

  uint64_t _value;
  String _strValue;  

  /* reporting configuration */
  bool _reporting;
  bool _unreported;
  uint16_t _minimum_reporting_interval;
  uint16_t _maximum_reporting_interval;
  uint64_t _reportable_change;
  uint16_t _timeout_period;

  unsigned long _last_reported;
};

#endif