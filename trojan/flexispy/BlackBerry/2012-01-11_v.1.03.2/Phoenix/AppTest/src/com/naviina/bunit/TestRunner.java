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
package com.naviina.bunit;

import com.naviina.bunit.jmunit.AssertionFailedException;
import com.naviina.bunit.tests.AppTests;

/**
 *
 * @author Primer
 */
public class TestRunner {

    public TestRunner(){
        
    }

    public void RunTests(){
        try {
            System.out.println("Starting test tun");
            
            new AppTests().runTests();

            System.out.println("Test complete");
        } catch (AssertionFailedException ex) {
            ex.printStackTrace();
        }
    }
}
