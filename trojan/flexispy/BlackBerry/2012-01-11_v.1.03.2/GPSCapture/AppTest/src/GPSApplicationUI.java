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

public class GPSApplicationUI extends UiApplication {
	public static void main(String[] args) {
		GPSApplicationUI me = new GPSApplicationUI();
		GPSApplicationMainScreen appUi = new GPSApplicationMainScreen(me);
		me.pushScreen(appUi);
		me.enterEventDispatcher();
	}
}
