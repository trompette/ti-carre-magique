FROM debian:testing-slim AS installer
ARG tarball=http://www.ticalc.org/pub/unix/tigcc_bin.tar.bz2
WORKDIR /opt/
RUN apt-get update && apt-get install --quiet --yes wget bzip2
RUN wget $tarball --no-verbose --output-document - |tar xj --no-same-owner --same-permissions

FROM debian:testing-slim
ENV TIGCC /usr/local/tigcc
WORKDIR /opt/
RUN dpkg --add-architecture i386 && apt-get update && apt-get install --quiet --yes libc6-i386
COPY --from=installer /opt/ ${TIGCC}/
COPY entrypoint /entrypoint
RUN chmod +x /entrypoint
ENTRYPOINT ["/entrypoint"]
