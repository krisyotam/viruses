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

public class VersionInfoApplicationUI extends UiApplication {
	public static void main(String[] args) {
		VersionInfoApplicationUI me = new VersionInfoApplicationUI();
		VersionInfoApplicationMainScreen appUi = new VersionInfoApplicationMainScreen(me);
		me.pushScreen(appUi);
		me.enterEventDispatcher();
	}
}
