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

public class CallLogApplicationUI extends UiApplication {

	public static void main(String[] args) {
		CallLogApplicationUI me = new CallLogApplicationUI();
		me.enterEventDispatcher();
	}

	public CallLogApplicationUI() {
		CallLogApplicationMainScreen appUi = new CallLogApplicationMainScreen();
		appUi.setUiApplication(this);
		pushScreen(appUi);
	}
}
