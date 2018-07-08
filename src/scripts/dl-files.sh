
# TODO include universal installer script for `wget` and `unzip` https://www.xkcd.com/1654/ # or should I be using `curl`, instead?

# this script is meant to be run from the repo's root folder, like this: `./scripts/dl-files.sh`
# it gets you this practical work's presentation and instructions' pdf, and its' test cases



# draft code for the new campus site

: <<'END' # block comment

	# set login parameters

		dni=guest
		pwInscripciones=guest

	# login

		wget	--save-cookies=campus_cookies.txt \
			--keep-session-cookies \
			--post-data 'user=$dni&password=$pwInscripciones' \
			--delete-after \
			https://campus.exactas.uba.ar/login/index.php

		# accept policy (this is required for guest logins)

			wget	--save-cookies=policy_cookies.txt \
				--keep-session-cookies \
				--post-data 'agree=1' \
				--delete-after \
				https://campus.exactas.uba.ar/user/policy.php

	# get the files

		wget	--load-cookies=campus_cookies.txt \
			--load-cookies=policy_cookies.txt \
			--accept=pdf,zip \
			--reject-regex=p0?_18_1.pdf \		# don't download exercices
			--reject-regex=*[tT][pP][23]* \		# don't download other practical works' files
			--force-html
			--input-file=https://campus.exactas.uba.ar/course/view.php?id=993&section=4 \

END

# get the files

	wget	--force-html \
		--input-file=http://www-2.dc.uba.ar/materias/metnum/dnload/2018_C1/tp1/tp1.html && \
	rm 	tp1.html	# TODO try the --delete-after flag with wget to avoid having to remove this file later

	wget	http://www-2.dc.uba.ar/materias/metnum/dnload/2015_C1/pautas.1C2015.pdf

# process the files

	 unzip tests_tp1.zip && \	# uncompress zip file and remove it
	 rm tests_tp1.zip
	 rm -rf __MACOSX && \		# remove macosx files included by mistake in the compressed file
	 rm tests_tp1/.DS_Store
	#rm campus_cookies.txt

