# HydrosFy

## Make Certificates

```bash
openssl req -x509 -newkey rsa:2048 -keyout ca_key.pem -out ca_cert.pem -days 365 -nodes
```

```txt
IMPORTANT! Common Name (CN) Must be the ip of the server 
```

## Start server for OTA

```bash
openssl s_server -WWW -key ca_key.pem -cert ca_cert.pem -port 8070
```
