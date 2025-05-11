# SPDX-FileCopyrightText: ©2021-2025 franklin <franklin@bitsmasher.net>
#
# SPDX-License-Identifier: MIT

CFLAGS=-I../include -g3 -DNDEBUG
CXXFLAGS=-I../include -g3 -DNDEBUG
# FCFLAGS=-m64

if DEBUG
override CFLAGS=-DDEBUG -g -femit-struct-debug-baseonly -Wall -Werror -Wextra -03
override CXXFLAGS=-DDEBUG -g -femit-struct-debug-baseonly -Wall -Werror -Wextra -03
endif

CLOCAL_AMFLAGS=-I config/m4 -I aclocal
ACLOCAL_AMFLAGS=-I config/m4 -I aclocal

.PHONY: docs python test terraform

clean: ## Clean up your mess
	rm -rf _build *.egg-info
	@find . -name '*.pyc' | xargs rm -rf
	@find . -name '__pycache__' | xargs rm -rf
	@for trash in _build aclocal.m4 autom4te.cache config config.in config.in~ config.log config.status configure configure~ libtool Makefile Makefile.in po stamp-h1 _test; do \
	if [ -f $$trash ] || [ -d $$trash ]; then \
		echo "Removing $$trash" ;\
		rm -rf $$trash ;\
	fi ; \
	done

python:
	@echo "Found Python version $(PY39)"
	@$(PYTHON) -m venv _build
	( \
		source _build/bin/activate; \
		_build/bin/python -m pip install --upgrade pip; \
		_build/bin/python -m pip install -r src/requirements.txt; \
	)

test: 
	@$(PY39) -m venv _test
	( \
		source _test/bin/activate; \
		_test/bin/python -m pip install --upgrade pip; \
		_test/bin/python -m pip install tox; \
		_test/bin/python -m pip install -r test/requirements-test.txt; \
		_test/bin/python -m pip install -r test/requirements-security.txt; \
	)
