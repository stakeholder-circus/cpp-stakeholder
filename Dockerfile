FROM alpine:3.20 AS build
RUN apk add --no-cache bash g++ make
WORKDIR /app
COPY Makefile ./
COPY src ./src
COPY tests ./tests
RUN make test

FROM alpine:3.20
RUN apk add --no-cache libstdc++
COPY --from=build /app/build/cpp-stakeholder /usr/local/bin/cpp-stakeholder
ENTRYPOINT ["cpp-stakeholder"]
