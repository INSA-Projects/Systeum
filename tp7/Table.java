

public class Table {
	int _taille;
	Object _baguettes[];
	
	Table(int t) {
		_taille = t;
		_bag = new Object[_taille];
		for (int i = 0; i < _taille; i++) {
			_bag[i]= new Object();
		}
	}
	
	void prendreBaguettes(int i) throws InterruptedException {
	    // TODO

	    System.out.println("J'ai une baguette "+_id);
	    sleep(100);


	    System.out.println("Je mange "+_id);
	    sleep(5000);


	}
	
}
