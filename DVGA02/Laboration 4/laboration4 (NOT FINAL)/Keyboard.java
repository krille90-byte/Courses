package laboration4_Test3;
import java.awt.event.KeyEvent;
import java.util.HashMap;



public class Keyboard {
	HashMap<Key, Boolean> state;
	public Keyboard() {
		state = new HashMap<Key, Boolean>();
		state.put(Key.Up, false);
		state.put(Key.Down, false);
		state.put(Key.Left, false);
		state.put(Key.Right, false);
		state.put(Key.Escape, false);
		state.put(Key.Enter, false);
		state.put(Key.Space, false);
		state.put(Key.P, false);
		state.put(Key.K, false);
		state.put(Key.One, false);
		state.put(Key.Two, false);
		state.put(Key.Tre, false);
		state.put(Key.Four, false);
		state.put(Key.Five, false);
		state.put(Key.Six, false);
	}
	
	public boolean isKeyDown(Key key) {
		if(state.containsKey(key)) {
			return state.get(key);
		}
		return false;
	}
	
	public boolean isKeyUp(Key key) {
		return !isKeyDown(key);
	}
	
	public void processKeyEvent(int key, boolean st) {
		switch(key) {
			case KeyEvent.VK_UP:     state.put(Key.Up,     st); break;
			case KeyEvent.VK_DOWN:   state.put(Key.Down,   st); break;
			case KeyEvent.VK_LEFT:   state.put(Key.Left,   st); break;
			case KeyEvent.VK_RIGHT:  state.put(Key.Right,  st); break;
			case KeyEvent.VK_ESCAPE: state.put(Key.Escape, st); break;
			case KeyEvent.VK_ENTER:  state.put(Key.Enter,  st); break;
			case KeyEvent.VK_SPACE:  state.put(Key.Space,  st); break;
			case KeyEvent.VK_P:		 state.put(Key.P,	   st); break;
			case KeyEvent.VK_K:		 state.put(Key.K,	   st); break;
			case KeyEvent.VK_1:	 	 state.put(Key.One,    st); break;
			case KeyEvent.VK_2:	 	 state.put(Key.Two,    st); break;
			case KeyEvent.VK_3:	 	 state.put(Key.Tre,    st); break;
			case KeyEvent.VK_4:	 	 state.put(Key.Four,   st); break;
			case KeyEvent.VK_5:	 	 state.put(Key.Five,   st); break;
			case KeyEvent.VK_6:	 	 state.put(Key.Six,    st); break;
		}
	}
	
}
