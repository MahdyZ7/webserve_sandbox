     #include <sys/event.h>
     #include <err.h>
     #include <fcntl.h>
     #include <stdio.h>
     #include <stdlib.h>
     #include <string.h>

     int
     main(int argc, char **argv)
     {
		struct	kevent event;	 /* Event we want to monitor */
		struct	kevent tevent;	 /* Event triggered */
		int kq, fd[argc - 1], ret;

		if (argc < 2)
			err(EXIT_FAILURE, "Usage: %s path\n", argv[0]);
		
		for (int i = 1; i < argc; i++)
		{
			fd[i - 1] = open(argv[i], O_RDONLY);
			if (fd[i - 1]	== -1)
				err(EXIT_FAILURE, "Failed to open '%s'", argv[i]);
		}
		// fd = open(argv[1], O_RDONLY);
		// if (fd	== -1)
		// 	err(EXIT_FAILURE, "Failed to open '%s'", argv[1]);

		/* Create kqueue. */
		kq = kqueue();
		if (kq	== -1)
			err(EXIT_FAILURE, "kqueue() failed");

		/* Initialize kevent structure. */
		for (int i = 0; i < argc - 1; i++)
			EV_SET(&event,	fd[i], EVFILT_VNODE, EV_ADD | EV_CLEAR, NOTE_WRITE, 0,	NULL);
		/* Attach event to the	kqueue.	*/
		ret = kevent(kq, &event, 1, NULL, 0, NULL);
		if (ret == -1)
			err(EXIT_FAILURE, "kevent register");
		if (event.flags & EV_ERROR)
			errx(EXIT_FAILURE,	"Event error: %s", strerror(event.data));

		for (;;) {
			/*	Sleep until something happens. */
			ret = kevent(kq, NULL, 0, &tevent,	1, NULL);
			if	(ret ==	-1) {
			err(EXIT_FAILURE, "kevent wait");
			} else if (ret > 0) {
			printf("Something was written in '%s'\n", argv[1]);
			}
		}
     }