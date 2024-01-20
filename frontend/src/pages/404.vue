<template>
  <div class="back">
    <div class="settings">
      <div class="info">
        <div class="ellipse_nav_logo"></div>
        <div class="profile_nickname">Nickname</div>
      </div>
      <div class="body">
        <profile-navbar class="profileNavbar"></profile-navbar>
        <div class="block_about_private_information">
          <input type="text" class="input_form_for_name" placeholder="Your name">
          <input type="text" class="input_form_for_surname" placeholder="Surname">
          <textarea name="message" rows="15" cols="50"
                    class="textarea_form_for_aboutMe" placeholder="About me"></textarea>
          <my-button class="btn_save">Save changes</my-button>
        </div>

        <div class="form_picture">
          <p class="picture_text">Profile picture</p>
          <div class="form_for_picture">
            <input type="file" id="file"
                   name="logo_for_profile" class="input_form_for_picture">
            <label class="TextBlock_in_container">
              <p class="text_in_containerPicture">Download</p>
              <p class="text_in_containerPicture">Remove</p>
            </label>
            <div class="ellipse_logo"></div>
          </div>
        </div>

        <div class="block_about_email">
          <p class="text_for_email">Your mailling addresses</p>
          <div class="current_email">
            <email-form></email-form>
            <email-form></email-form>
            <email-form></email-form>
          </div>
          <input type="text" class="input_for_email" placeholder="New mailling addresses">
          <div class="container_for_btn_addEmail">
            <my-button>Add email</my-button>
          </div>
        </div>

        <div class="block_about_password">
          <p class="new_password_title">New password</p>
          <input type="password" class="input_form_for_password" placeholder="Current password">
          <input type="password" class="input_form_for_password" placeholder="New password">
          <input type="password" class="input_form_for_password" placeholder="New password(repeat)">
          <div class="block_for_btn_savePassword">
            <my-button class="btn_savePassword"></my-button>
          </div>
          <p class="forget_password_title">Forget password?</p>
          <p class="text_forget_password">Enter your email address, and we will send you an email with which you can reset your password.</p>
          <input type="email" class="input_form_for_email" placeholder="Email address">
          <div class="block_for_btn_savePassword">
            <my-button class="btn_savePassword"></my-button>
          </div>
        </div>

        <div class="block_about_deleteAccount">
          <p class="title_delete_account">Delete account</p>
          <p class="text_warning">Once you delete your account, there is no going back. Please be certain.</p>
          <my-button class="btn_delete_account">Delete your account</my-button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import EventNavbar from "@/components/UI/EventNavbar.vue";
import MyButton from "@/components/UI/MyButton.vue";
import ProfileNavbar from "@/components/UI/ProfileNavbar.vue";
import EmailForm from "@/components/UI/EmailForm.vue";

export default {
  components: {EmailForm, ProfileNavbar, MyButton, EventNavbar}

}
</script>

<style scoped>

.title {
  color: #081b29;
  background-color: #0d1117;
}
</style>