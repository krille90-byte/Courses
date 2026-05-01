package laboration4_Test3;

import java.awt.Color;
import java.awt.Dimension;
import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.JLabel;

public class LatestList {


private DefaultListModel dlm;
private ArrayList<Integer> arrayScore = new ArrayList();
	public LatestList()
	{
		dlm = new DefaultListModel();
		dlm.add(0, "LatestPoints: ");
		
	}
	
		public void add(int score)
		{
			if(dlm.size()==4) {
				dlm.remove(3);
			}
			dlm.add(1, score);
			
			
			
			
			
			/*arrayScore.add(anElement);
			dlm.removeAllElements();
			
			for(int i = 0; i < arrayScore.size(); i++) {
				
				dlm.add(i,(i+1)+". "+arrayScore.get(i));
				
				
			}
			if(!dlm.isEmpty()) {
				dlm.add(0, "LatestPoints: ");
			}
			if(dlm.size()>4) {
				dlm.removeElementAt(4);
			}*/
		}
				public DefaultListModel getList()
				{
					return dlm;
				}
	
		
}

