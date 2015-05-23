
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
		type &				getAt(int index);
		int					getIterPosition (); 		

		int					size();


	typedef struct Node{				
		type *				data;
		Node *				prev;
		Node *				next;

	}node_t;
			
		int					count;
		

		Node *				root;
		Node *				leaf;
		Node *				iterator;

private:
		Node *				createNode(type &e, Node *p, Node *n, int increment);
		void				deleteNode(Node *node, int decrement);
		void				updateNodeLinks(Node *node, const char *str);
			
};


		
		
