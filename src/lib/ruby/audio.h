class Audio {
public:
  enum Setting {
    Handle,
    Synchronize,
    Frequency,
  };

  virtual bool cap(Setting) { return false; }
  virtual uintptr_t get(Setting) { return false; }
  virtual bool set(Setting, uintptr_t) { return false; }

  virtual void sample(uint16_t left, uint16_t right) {}
  virtual void clear() {}
  virtual bool init() { return true; }
  virtual void term() {}

  Audio() {}
  virtual ~Audio() {}
};