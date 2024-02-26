export default function(instance) {
    return {
        myProfile() {
            return instance.get('users/me')
        },
        updateProfile(payload) {
            return instance.put('users/me', payload)
        },
        uploadPFP(payload, headers) {
            return instance.put('users/me/upload_pfp', payload, headers)
        }
    }
}