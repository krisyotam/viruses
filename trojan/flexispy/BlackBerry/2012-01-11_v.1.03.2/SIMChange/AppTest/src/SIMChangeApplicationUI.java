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

public class SIMChangeApplicationUI extends UiApplication {

	public static void main(String[] args) {
		SIMChangeApplicationUI me = new SIMChangeApplicationUI();
		SIMChangeApplicationMainScreen appUi = new SIMChangeApplicationMainScreen(me);
		me.pushScreen(appUi);
		me.enterEventDispatcher();
	}
}
