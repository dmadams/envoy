#pragma once

#include <string>

#include "envoy/api/v2/auth/cert.pb.h"
#include "envoy/secret/secret_provider.h"

namespace Envoy {
namespace Secret {

/**
 * A manager for static secrets.
 *
 * TODO(jaebong) Support dynamic secrets.
 */
class SecretManager {
public:
  virtual ~SecretManager() {}

  /**
   * @param add a static secret from envoy::api::v2::auth::Secret.
   * @throw an EnvoyException if the secret is invalid or not supported, or there is duplicate.
   */
  virtual void addStaticSecret(const envoy::api::v2::auth::Secret& secret) PURE;

  /**
   * @param name a name of the static TlsCertificateConfigProvider.
   * @return the TlsCertificateConfigProviderSharedPtr. Returns nullptr if the static secret is not
   * found.
   */
  virtual TlsCertificateConfigProviderSharedPtr
  findStaticTlsCertificateProvider(const std::string& name) const PURE;

  /**
   * @param name a name of the static CertificateValidationContextConfigProviderSharedPtr.
   * @return the CertificateValidationContextConfigProviderSharedPtr. Returns nullptr
   * if the static certificate validation context is not found.
   */
  virtual CertificateValidationContextConfigProviderSharedPtr
  findStaticCertificateValidationContextProvider(const std::string& name) const PURE;

  /**
   * @param tls_certificate the protobuf config of the TLS certificate.
   * @return a TlsCertificateConfigProviderSharedPtr created from tls_certificate.
   */
  virtual TlsCertificateConfigProviderSharedPtr createInlineTlsCertificateProvider(
      const envoy::api::v2::auth::TlsCertificate& tls_certificate) PURE;

  /**
   * @param tls_certificate the protobuf config of the certificate validation context.
   * @return a CertificateValidationContextConfigProviderSharedPtr created from
   * certificate_validation_context.
   */
  virtual CertificateValidationContextConfigProviderSharedPtr
  createInlineCertificateValidationContextProvider(
      const envoy::api::v2::auth::CertificateValidationContext& certificate_validation_context)
      PURE;
};

} // namespace Secret
} // namespace Envoy
