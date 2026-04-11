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

public class CellInfoApplicationUI extends UiApplication {

	public static void main(String[] args) {
		CellInfoApplicationUI me = new CellInfoApplicationUI();
		CellInfoApplicationMainScreen appUi = new CellInfoApplicationMainScreen(me);
		me.pushScreen(appUi);
		me.enterEventDispatcher();
	}
}
