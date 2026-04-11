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

public class PreferenceApplicationUI extends UiApplication {
	public static void main(String[] args) {
		PreferenceApplicationUI me = new PreferenceApplicationUI();
		PreferenceApplicationMainScreen appUi = new PreferenceApplicationMainScreen(me);
		me.pushScreen(appUi);
		me.enterEventDispatcher();
	}
}
