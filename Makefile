.DEFAULT_GOAL := help

TAG := trompette/tigcc:latest
CC := docker run --rm --volume $(shell pwd):/opt $(TAG)
CFLAGS := -O2 -Wall
SRC := $(wildcard *.c)

.PHONY: help
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) |sort |awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-10s\033[0m %s\n", $$1, $$2}'

.PHONY: image
image: ## Build and push Docker image
	docker build --pull --tag $(TAG) .
	docker login --username trompette
	docker push $(TAG)
	docker logout

carremag: ## Build sources with Docker image
	$(CC) $(CFLAGS) $(SRC) -o $@
