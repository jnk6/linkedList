
template <typename type> class linkedList{
	public:
							linkedList();
		virtual				~linkedList();
		bool				add (type &object); 
		bool				insert(int index, type &object);
		bool				addTail (type &object);
		bool				addHead (type &object);

		type &				getHead ();
		type &				getTail ();
		int					getHeadPosition (); //?
		type &				removeAt(int index);
		int					getIterPosition (); 		

		int					size();


	struct Node{

		type &				data;
		Node *				prev;
		Node *				next;

	};
			
		int					count;
		

		Node *				root;
		Node *				leaf;
		Node *				iterator;
			
};


		
		
