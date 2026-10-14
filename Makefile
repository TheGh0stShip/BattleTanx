PYTHON ?= python3
VENV := .venv
VENV_PYTHON := $(VENV)/bin/python
VENV_STAMP := $(VENV)/.installed
ROM := baseroms/us/baserom.z64

.PHONY: all setup toolchain verify config split verify-matching check clean-generated

all: split

$(VENV_STAMP): requirements.txt
	$(PYTHON) -m venv $(VENV)
	$(VENV_PYTHON) -m pip install --upgrade pip
	$(VENV_PYTHON) -m pip install -r requirements.txt
	touch $(VENV_STAMP)

config:
	$(PYTHON) tools/generate_splat_config.py

setup: $(VENV_STAMP) config

toolchain:
	tools/bootstrap_ido.sh

verify:
	$(PYTHON) tools/verify_rom.py $(ROM)

split: setup verify
	$(VENV_PYTHON) -m splat split config/us/splat.yaml

verify-matching: verify toolchain
	$(PYTHON) tools/verify_matching_units.py --rom $(ROM)

check: config
	$(PYTHON) -m unittest discover -s tests -v
	$(PYTHON) tools/check_repository.py

clean-generated:
	rm -rf asm build .splache
